# ESPHome Puerta + Timbre — Definición del Sistema

Sistema autónomo para control de acceso de puerta con timbre musical,
apertura temporizada, señalización visual y audible, y corte de
emergencia físico. Basado en NodeMCU ESP8266 con ESPHome, sin
dependencia de Home Assistant ni MQTT. Todo el cableado entre zonas
sobre un solo UTP Cat5 de 4 pares, sin cables adicionales.

## Distribución Física

```
  ┌─────────────────────────────────────────────────────────────────────┐
  │                           SALÓN                                     │
  │  ┌──────────────────────────────────────────────────────────────┐  │
  │  │  Panel de control                                            │  │
  │  │  ┌──────────┐  ┌──────────┐  ┌──────────┐                  │  │
  │  │  │ Pulsador │  │ LED      │  │ Buzzer   │  ← abre + oye    │  │
  │  │  │ Interno  │  │ Estado   │  │ Musical  │     timbre       │  │
  │  │  └──────────┘  └──────────┘  └──────────┘                  │  │
  │  └──────────────────────────────────────────────────────────────┘  │
  └──────────────────────────┬──────────────────────────────────────────┘
                             │
  ┌──────────────────────────┴──────────────────────────────────────────┐
  │                         VESTÍBULO                                   │
  │  ┌──────────┐  ┌──────────────────────────────────────────────┐  │
  │  │ Módulo   │  │  Panel de control (réplica)                  │  │
  │  │ MCU      │  │  ┌──────────┐  ┌──────────┐  ┌────────┐     │  │
  │  │ ┌──────┐ │  │  │ Pulsador │  │ LED      │  │ Buzzer │     │  │
  │  │ │NodeMCU│ │  │  │ Interno  │  │ Estado   │  │ Musical│     │  │
  │  │ │Fuente │ │  │  └──────────┘  └──────────┘  └────────┘     │  │
  │  │ │ 5V    │ │  └──────────────────────────────────────────────┘  │
  │  │ │Fuente │ │                                                    │
  │  │ │ 12V   │ │                                                    │
  │  │ │Relé   │ │                                                    │
  │  │ └──────┘ │                                                    │
  │  └──────────┘                                                    │
  └──────────────────────────┬──────────────────────────────────────────┘
                             │
  ┌──────────────────────────┴──────────────────────────────────────────┐
  │                           PATIO                                     │
  │  ┌──────────────────────────────────────────────────────────────┐  │
  │  │  Panel de timbre                                             │  │
  │  │  ┌──────────────┐  ┌──────────┐  ┌──────────┐              │  │
  │  │  │   Pulsador   │  │ LED      │  │ Buzzer   │  ← solicita  │  │
  │  │  │   Externo    │  │ Estado   │  │ Musical  │     entrada  │  │
  │  │  └──────────────┘  └──────────┘  └──────────┘              │  │
  │  └──────────────────────────────────────────────────────────────┘  │
  │  ┌──────────────────────────────────────────────────────────────┐  │
  │  │  Pedal de apertura de emergencia                            │  │
  │  │  ┌──────────────────────────────┐                            │  │
  │  │  │ NC en serie con alimentación │  ← corte físico únicamente │  │
  │  │  │ cerradura (sin señal a MCU)  │     (no va al NodeMCU)     │  │
  │  │  └──────────────────────────────┘                            │  │
  │  └──────────────────────────────────────────────────────────────┘  │
  │  ┌──────────────────────────────────────────────────────────────┐  │
  │  │  Cerradura Magnética + Final de Carrera                     │  │
  │  │  ┌──────────────────────┐                                    │  │
  │  │  │ Cerradura (12V)     │  ← alimentación vía relé NC        │  │
  │  │  │ Final carrera (NA)  │  ← GPIO13                          │  │
  │  │  └──────────────────────┘                                    │  │
  │  └──────────────────────────────────────────────────────────────┘  │
  └──────────────────────────┬──────────────────────────────────────────┘
                             │
  ┌──────────────────────────┴──────────────────────────────────────────┐
  │                         EXTERIOR                                   │
  │  ┌──────────────────────────────────────────────────────────────┐  │
  │  │  Panel de timbre                                             │  │
  │  │  ┌──────────────┐  ┌──────────┐  ┌──────────┐              │  │
  │  │  │   Pulsador   │  │ LED      │  │ Buzzer   │  ← solicita  │  │
  │  │  │   Externo    │  │ Estado   │  │ Musical  │     entrada  │  │
  │  │  └──────────────┘  └──────────┘  └──────────┘              │  │
  │  └──────────────────────────────────────────────────────────────┘  │
  └─────────────────────────────────────────────────────────────────────┘
```

## Cableado (UTP Cat5, 4 pares)

| Par | Hilo | Señal | Destino |
|-----|------|-------|---------|
| 1 | BL | GPIO4 (pulsador interno) | Salón |
| 1 | NA | GND | Salón |
| 2 | BL/V | GPIO16 (pulsador externo) | Patio + Ext. |
| 2 | V | **12V conmutado** (LEDs vía transistor) | Todas las zonas |
| 3 | BL/AZ | GPIO14 (buzzer musical) | Todas las zonas |
| 3 | AZ | GND | Todas las zonas |
| 4 | BL/MR | Relay NC (12V cerradura) | Patio |
| 4 | MR | GPIO13 (final carrera) | Patio |

El retorno GND de la cerradura va por los hilos NA y AZ (pares 1 y 3). La alimentación 5V del NodeMCU es local en el módulo del vestíbulo.

## 1. Resumen de Hardware

| Componente | Propósito |
|-----------|-----------|
| NodeMCU ESP8266 | Microcontrolador ejecutando ESPHome |
| Fuente 5V | Alimentación NodeMCU (local en vestíbulo) |
| Fuente 12V | Alimentación cerradura + LEDs (local en vestíbulo) |
| Relé | Conmuta 12V de la cerradura. NC: cerradura alimentada (puerta cerrada). NA: libre. |
| Cerradura Magnética | Mantiene la puerta cerrada mientras recibe 12V |
| Buzzer Musical (RTTTL) | Zumbador piezoeléctrico — melodía timbre, pitidos desbloqueo y alarma de emergencia. Una unidad por zona (×4). |
| Pulsadores Internos (×2) | Salón y vestíbulo — GPIO4 en paralelo |
| Pulsadores Externos (×2) | Patio y exterior — GPIO16 en paralelo |
| LEDs Estado 12V (×4) | Todas las zonas — conmutados por transistor único |
| Transistor NPN (BC337) | Conmuta 12V a los LEDs desde GPIO12 |
| Final de Carrera (NA) | GPIO13 — detecta puerta abierta/cerrada y apertura por emergencia |
| Pedal de Emergencia | Corte físico: NC en serie con 12V de la cerradura. Sin señal al MCU. |

## 2. Asignación de Pines

| GPIO | Componente | Tipo |
|------|-----------|------|
| GPIO4 | Pulsadores internos (salón + vestíbulo, paralelo) | Entrada (pull-up, invertido) |
| GPIO16 | Pulsadores externos (patio + exterior, paralelo) | Entrada (pull-up ext. 10kΩ, NA a GND) |
| GPIO12 | Base transistor NPN (BC337) → conmuta 12V a LEDs | Salida (PWM, 1kΩ en serie) |
| GPIO14 | Buzzer Musical (×4, todas, paralelo) | Salida (PWM 2000 Hz, RTTTL) |
| GPIO5 | Relé de Cerradura (NC → lock, NA → libre) | Salida (relé) |
| GPIO13 | Final de Carrera + detección emergencia | Entrada (pull-up, NA) |

## 3. Definición de Componentes

### 3.1 Pulsadores Internos (panel de control)
- **Pin**: GPIO4, `INPUT_PULLUP`, invertido. Paralelo salón + vestíbulo.
- **Pulsación corta** (< 4s): ejecuta `internal_press` (solo en ACTIVADO)
- **Pulsación larga** (> 4s): si sistema DESACTIVADO → `enable_system`
- **Pulsación muy larga** (> 8s): si sistema ACTIVADO → `disable_system`

### 3.2 Pulsadores Externos (panel de timbre)
- **Pin**: GPIO16, `INPUT` con pull-up ext. 10kΩ. Paralelo patio + exterior.
- **Pulsación corta** (< 4s): ejecuta `external_press` (solo timbre, NO desbloquea)
- Pulsaciones largas ignoradas (solo el panel de control interno tiene función de mantenimiento)

### 3.3 Relé
- GPIO5. **ID**: `lock_relay_output`
- **OFF** → NC cerrado → cerradura recibe 12V → puerta cerrada
- **ON** → NC abierto → cerradura pierde 12V → puerta desbloqueada
- NA no se usa

### 3.4 Final de Carrera
- GPIO13. INPUT_PULLUP. NA a GND.
- **ON**: puerta abierta. **OFF**: puerta cerrada.
- Si se activa con relé OFF → apertura por emergencia

### 3.5 Buzzer Musical (RTTTL)
- GPIO14 (PWM). Paralelo a todas las zonas.
- Soporta dos modos:
  - **RTTTL**: melodías de timbre (4 programables por el usuario en `melodies.h`)
  - **Control directo PWM**: pitidos de advertencia y alarma (generados por script)
- Cada pulsación del timbre (externo) reproduce la siguiente melodía RTTTL en secuencia.
- Al abrirse la puerta tras desbloqueo interno, el índice se resetea a la melodía 1.
- Durante el desbloqueo suenan pitidos de advertencia (control directo PWM), no melodía.
- La alarma de emergencia usa control directo PWM.

### 3.6 LEDs Estado
- GPIO12 → 1kΩ → base BC337 (NPN). Colector conmuta 12V a todas las zonas.
- Emisor a GND. 12V común al ánodo de cada LED, cátodo vía resistor limitador (470Ω) al hilo de colector.
- PWM desde GPIO12 controla el transistor, los cuatro LEDs reciben el mismo brillo.
- **Efectos:**
  - *Latido suave*: oscilación 50%–100% con transición de 1s
  - *Flash rápido*: 200ms ON / 200ms OFF
  - *Flash lento*: duración configurable (`gate_open_flash_interval`), acompañado de pitido corto

## 4. Estado del Sistema

El sistema tiene dos estados:

| Estado | Relé | Pulsadores | LED | Uso |
|--------|------|-----------|-----|-----|
| **DESACTIVADO** (boot) | ON (puerta desbloqueada) | Ignorados | OFF | Mantenimiento / emergencia |
| **ACTIVADO** | Según `unlock_gate` | Operación normal | 25% brillo (reposo) | Uso diario |

Transiciones:
- Boot → DESACTIVADO
- DESACTIVADO + pulsación interna >4s → ACTIVADO
- ACTIVADO + pulsación interna >8s → DESACTIVADO

## 5. Detección de Emergencia

```
Al recibir final carrera = ON:
  Si lock_relay_output está ON → desbloqueo normal
  Si lock_relay_output está OFF → apertura no autorizada (pedal/forzada)
     → emergency_alert
```

## 6. Comportamiento

| Evento | Relé (cerradura) | Buzzer Musical (RTTTL) | LED |
|--------|-----------------|----------------------|-----|
| **Sistema DESACTIVADO** | ON (permanentemente) | — | OFF |
| **Sistema ACTIVADO** (reposo) | — | — | 25% brillo |
| Pulsación int. >4s (DESACTIVADO → ACTIVADO) | OFF | Secuencia activación | 3 flashes rápidos → 25% |
| Pulsación int. >8s (ACTIVADO → DESACTIVADO) | ON perm. | Secuencia desactivación | 3 flashes lentos → OFF |
| Pulsador externo (ACTIVADO) | — | Melodía actual | Latido suave 100% `doorbell_led_duration` |
| Pulsador interno (ACTIVADO) | ON `unlock_duration` | Pitidos metro Londres | Flash rápido durante desbloqueo |
| Puerta abierta tras desbloqueo | OFF | pitido corto sincronizado con el flash | Flash lento `gate_open_flash_interval` |
| Puerta cerrada tras desbloqueo | OFF | — | 25% brillo (reposo) |
| Emergencia (FC ON, relé OFF) | — | Alarma tono alternado 800/1200Hz | Fast Flash 10s |

Mientras el sistema está DESACTIVADO el relé permanece ON y cualquier pulsación (externa o interna) es ignorada.
Los pulsadores externos **nunca desbloquean** la puerta — solo tocan el timbre.

## 7. Scripts

### 7.1 `external_press` (patio / exterior — timbre)
```
1. Si sistema DESACTIVADO → salir
2. Si LED no está en reposo (cooldown) → salir (ignorar)
3. Cancelar timer_reset_melodia (si existe)
4. Reproducir melodía actual (RTTTL, no bloqueante)
5. LED → LATIDO SUAVE al 100%
6. Esperar doorbell_led_duration
7. LED → 25% (reposo)
8. índice de melodía + 1
9. Iniciar timer_reset_melodia (60s)
```

Si transcurren 60s sin una nueva pulsación externa, el timer resetea
el índice de melodía a 0. Si ocurre una nueva pulsación antes, el
timer se cancela (paso 3) y se reinicia al final del cooldown (paso 9).

### 7.2 `internal_press` (salón / vestíbulo — abrir puerta)
```
1. Si sistema DESACTIVADO → salir
2. Ejecutar unlock_gate
3. Esperar doorbell_led_duration  (tiempo de bloqueo para nueva apertura)
4.    Si final carrera = ON → LED → flash lento + pitido corto (gate_open_flash_interval)
                            índice de melodía → 0 (reseta playlist)
   Si no → LED → 25% (reposo)
```

El interno no reproduce melodía, no avanza el índice de melodía,
y no comparte cooldown con el externo — son independientes.

### 7.3 `unlock_gate`
```
1. Relé → ON
2. Iniciar flash_and_beep (segundo plano)
3. Esperar hasta: final carrera ON  O  unlock_duration
4. Relé → OFF
5. Detener flash_and_beep. Apagar buzzer.
```

> `unlock_gate` **no controla el LED**. El LED lo gestiona `internal_press`
> (flash rápido durante desbloqueo, luego flash lento o 25% según estado de la puerta).

### 7.4 `flash_and_beep`
Mientras `lock_relay_output` esté ON, reproduce el pitido de advertencia
estilo **metro de Londres** (pitidos cortos que se aceleran):

```
vuelta 1: beep · · · 400ms pausa
vuelta 2: beep · · · 350ms pausa
vuelta 3: beep · · · 300ms pausa
vuelta 4: beep · · · 250ms pausa
vuelta 5: beep · · · 200ms pausa
vuelta 6: beep · · · 150ms pausa
vuelta 7: beep · · · 100ms pausa
vuelta 8: beep · · ·  75ms pausa
... acelera hasta 50ms y se mantiene
```

Cada "beep" = 80ms de tono PWM a ~1000 Hz. El ciclo se repite hasta que el relé se apaga.

El LED no se ve afectado por este script — tras el desbloqueo
`internal_press` se encarga del estado final del LED.

### 7.5 `enable_system`
```
1. Sistema → ACTIVADO
2. Reproducir secuencia ascendente (3 notas cortas)
3. LED: 3 flashes rápidos → 25% (reposo)
4. Relé → OFF (cerradura bloqueada)
```

### 7.6 `disable_system`
```
1. Sistema → DESACTIVADO
2. Reproducir secuencia descendente (3 notas largas)
3. LED: 3 flashes lentos → OFF
4. Relé → ON permanentemente (cerradura desbloqueada)
```

### 7.7 `emergency_alert`
```
1. Alarma de emergencia (control directo PWM, tono alternado):
   500ms a 800 Hz · 500ms a 1200 Hz · repetido 5 veces
2. LED → FLASH RÁPIDO sincronizado con la alarma
3. Tras alarma, si sigue abierta → flash lento + pitido (gate_open_flash_interval)
   Si no → LED → 25% (reposo), silencio
```

## 8. Comunicación

| Método | Propósito |
|--------|-----------|
| WiFi | Red local + AP respaldo |
| Web Server | http://<ip>/ — control manual |
| OTA | Actualizaciones |

Sin HA, API nativa ni MQTT.

## 9. Parámetros

| Parámetro | Default | Configurable | Descripción |
|-----------|---------|-------------|-------------|
| `unlock_duration` | 5s | No | Tiempo que la cerradura permanece desbloqueada |
| `doorbell_led_duration` | 45s | Web (10–120s) | Duración del latido suave del LED al pulsar timbre |
| `gate_open_flash_interval` | 5s | Web (1–30s) | Intervalo de flasheo del LED cuando puerta está abierta |
| `melody_reset_timeout` | 60s | No | Tiempo sin pulsaciones externas tras el cooldown que resetea el índice de melodía a 0 |

## 10. Repertorio de Melodías (RTTTL)

4 melodías en formato RTTTL. Cada pulsación del timbre externo
reproduce la siguiente. Al llegar a la cuarta vuelve a la primera.
El ciclo se resetea a la melodía 1 cuando el final de carrera detecta
apertura tras desbloqueo interno.

| # | Código RTTTL |
|---|--------------|
| 1 | `d=4,o=4,b=100:a,8c5,8c5,1g,a,c5,b,a,2g` |
| 2 | `d=4,o=4,b=100:f,a,c5,2g,a,c5,b,a,2g` |
| 3 | `d=4,o=4,b=100:g,g,2a,a,g,f,g,2e` |
| 4 | `d=4,o=4,b=100:8p,8a,b,c5,c5,b,a,g,a,8g,8f,16e,16d,8c` |

Las cadenas se definen como constantes en el YAML (mediante `globals` o lambdas).

## 11. Archivos

```
esphome-gate/
├── SYSTEM_DEFINITION.md
├── esphome-gate.yaml       # (generar a partir de la definición)
└── secrets.yaml            # (crear) WiFi password
```
