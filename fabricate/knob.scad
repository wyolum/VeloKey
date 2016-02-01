D = 34.5;
thumb_d = 18;
H = 14;
T = 2;

difference(){
  intersection(){
    cylinder(d=D, h=H, $fn=100);
    cylinder(h=2*H, d1=2*D-4, d2=0, $fn=100);
  }

  difference(){
    translate([0, 0, -1])
      cylinder(d=D - 2 * T, h=H-T + 1);
    translate([0, 0, 6])
      cylinder(d=D/3, h=H-T + 1);
  }
  difference(){
    translate([0, 0, -1])
      cylinder(d=6, h=H - T + 1, $fn=100);
    translate([1.5, -50, 0])cube([3, 100, 100]);
  }
  translate([.3 * D, 0, H + thumb_d/2 - 1.75])sphere(d=thumb_d, $fn=26);
}
