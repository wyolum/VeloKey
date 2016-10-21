magnet_h = 2.33;
magnet_d = 11;
center = [0, -17.75, -16.3];

inch = 25.4;
//translate([0, 17.5, 20])import("OTS2_5_bot.stl");

difference(){
  translate([0, 17.5, -1.])linear_extrude(height=1)projection()import("OTS2_5_bot.stl");

  for(i=[0:3]){
    theta = i * 90 + 45;
    translate([magnet_d * cos(theta), magnet_d * sin(theta), -1])
      color([0, 1, 0])cylinder(h=1, d=4, $fn=50);
  }
  translate([0, 0, -22])cylinder(h=23, d=1.5, $fn=30);
}

translate([0, 0, -10])rotate(a=180, v=[1, 0, 0])rotate(a=90, v=[0, 0, 1])
difference(){
  union(){
    difference(){
      import("Garmin_Quarter_Turn_Plate.stl");
      // cylinder(d=40, h=5);
      translate([0, 0, -2])cylinder(h=23, d=1.5, $fn=30);
      translate([0, 0, 2])cylinder(h=5, d=3.5, $fn=30);
    }
    for(i=[0:3]){
      theta = i * 90 + 45;
      translate([magnet_d * cos(theta), magnet_d * sin(theta), -1])
	color([0, 1, 0])cylinder(h=1, d2=4, d1=3, $fn=50);
    }
  }
  for(i=[0:3]){
    theta = i * 90;
    translate([magnet_d * cos(theta), magnet_d * sin(theta), 0])
      color([0, 1, 0])cylinder(h=magnet_h, d=magnet_d, $fn=50);
  }
}
cylinder(h=.15*inch, d1=.25*inch, d2=0, $fn=50);
