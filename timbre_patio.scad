/* Abrepuertas — Caja para electrónica
 * 50 mm × 80 mm × 50 mm
 * Frente = plano XY, profundidad = eje Z
 * Apertura en la pared derecha (x = ancho/2).
 * Pestañas con tornillos en las 4 esquinas de la pared derecha.
 * Agujeros de timbre y LED en la pared frontal (z = fondo/2).
 */

// --- parámetros (en décimas de mm) ----------------------------------
grosor_linea  = 4;    // 0.4 mm
num_paredes   = 3;    // número de perímetros
bisel         = 12;   // 1.2 mm (chaflán 45° en esquinas verticales)

ancho         = 500;  // 50.0 mm
alto          = 800;  // 80.0 mm
fondo         = 500;  // 50.0 mm

diam_timbre   = 120;  // 12.0 mm
pos_x_timbre  = 0;
pos_y_timbre  = 0;

diam_led      = 50;   // 5.0 mm
pos_x_led     = 0;
pos_y_led     = 180;
usar_led      = 1;

diam_tornillo = 50;   // 5.0 mm
dist_tornillo = 50;   // 5.0 mm

largo_pestanna = 210; // 21.0 mm
prof_pestanna  = 100; // 10.0 mm
solape         = 1;    // 0.1 mm

// --- conversión a mm -------------------------------------------------
_mm = 0.1;
_w = num_paredes * grosor_linea * _mm;
_b = bisel * _mm;
_wid = ancho * _mm;
_h = alto * _mm;
_d = fondo * _mm;

_dt = diam_timbre * _mm;
_pxt = pos_x_timbre * _mm;
_pyt = pos_y_timbre * _mm;
_dl = diam_led * _mm;
_pxl = pos_x_led * _mm;
_pyl = pos_y_led * _mm;
_ul = usar_led;

_dh = diam_tornillo * _mm;
_ho = dist_tornillo * _mm;
_tl = largo_pestanna * _mm;
_td = prof_pestanna * _mm;
_so = solape * _mm;

// --- helpers ----------------------------------------------------------
module chamfered_square(sx, sy, c) {
    if (c > 0.001) {
        x = sx/2;
        y = sy/2;
        polygon([
            [ x - c,  y], [ x,  y - c],
            [ x, -y + c], [ x - c, -y],
            [-x + c, -y], [-x, -y + c],
            [-x,  y - c], [-x + c,  y]
        ]);
    } else {
        square([sx, sy], center = true);
    }
}

module box_body() {
    linear_extrude(height = _d, center = true)
        chamfered_square(_wid, _h, _b);
}

module cavity() {
    linear_extrude(height = _d - 2*_w + 0.01, center = true)
        chamfered_square(_wid - 2*_w, _h - 2*_w, _b - _w);
}

module right_side_cut() {
    translate([_wid/2 - _w/2, 0, 0])
        cube([_w + 0.01, _h + 1, _d + 1], center = true);
}

// --- pestañas triangulares (pared derecha) ---------------------------
module screw_tab() {
    difference() {
        rotate([0, -90, 0])
            linear_extrude(height = _td)
                polygon(points = [[_so, _so], [-_tl, _so], [_so, -_tl]]);
        translate([0, -_ho, -_ho])
            rotate([0, -90, 0])
                cylinder(h = _td + 0.02, d = _dh, $fn = 24);
    }
}

module pestannas() {
    x0 = _wid/2 - _w;
    for (sy = [1, -1], sz = [1, -1])
        translate([x0, sy * (_h/2 - _w), sz * (_d/2 - _w)])
            scale([1, sy, sz])
                screw_tab();
}

// --- agujeros frontales (z = fondo/2) --------------------------------
module front_cutouts() {
    translate([_pxt, _pyt, _d/2])
        cylinder(h = _w + 0.02, d = _dt, center = true, $fn = 48);
    if (_ul)
        translate([_pxl, _pyl, _d/2])
            cylinder(h = _w + 0.02, d = _dl, center = true, $fn = 32);
}

// --- ensamblado -------------------------------------------------------
union() {
    difference() {
        box_body();
        cavity();
        right_side_cut();
        front_cutouts();
    }
    pestannas();
}