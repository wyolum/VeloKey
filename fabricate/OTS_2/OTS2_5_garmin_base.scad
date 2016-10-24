magnet_h = 2.33;
magnet_d = 11.11;
center = [0, -17.75, -16.3];

inch = 25.4;
//translate([0, 17.5, 20])import("OTS2_5_bot.stl");

// outrigger aligment bumpers
color([0, 0, 1])translate([44, 17, -1])cylinder(d=.25*inch, h=3);
color([0, 0, 1])translate([-44, 17, -1])cylinder(d=.25*inch, h=3);
color([0, 1, 1])translate([44, 17, 1])
difference(){
  scale([1, 1, .5])sphere(d=.25*inch, $fn=50);
  translate([-5, -5, -10])cube([10, 10, 10]);
}
color([0, 1, 1])translate([-44, 17, 1])
difference(){
  scale([1, 1, .5])sphere(d=.25*inch, $fn=50);
  translate([-5, -5, -10])cube([10, 10, 10]);
}

difference(){
  translate([0, 17.5, -1.])linear_extrude(height=3)projection()import("OTS2_5_bot.stl");

  /*
  for(i=[0:3]){ // alighment holes
    theta = i * 90 + 45;
    translate([magnet_d * cos(theta), magnet_d * sin(theta), -2])
      color([0, 1, 5])cylinder(h=10, d=4, $fn=50);
  }
  */
  translate([0, 0, -50])cylinder(h=100, d=1.5, $fn=30);

  for(i=[0:3]){ // magnet holes
    theta = i * 90;
    translate([magnet_d * cos(theta), magnet_d * sin(theta), -1])
      {
	color([0, 1, 0])cylinder(h=magnet_h, d=magnet_d, $fn=50);
	color([0, 1, 0])cylinder(h=magnet_h * 10, d=magnet_d-2, $fn=50);
      }
  }
  
}

difference(){
  translate([0, 0, 1])cylinder(h=.15*inch, d1=.25*inch, d2=0, $fn=50);
  translate([0, 0, -50])cylinder(h=100, d=1.5, $fn=30);

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
    /* // let magnets be aligment studs
    for(i=[0:3]){ // alignment studs
      theta = i * 90 + 45;
      translate([magnet_d * cos(theta), magnet_d * sin(theta), -1])
	color([0, 1, 0])cylinder(h=1, d2=3.5, d1=3, $fn=50);
    }
    */
  }
  /*
  */
  for(i=[0:3]){ // magnet holes in garmin base
    theta = i * 90;
    translate([magnet_d * cos(theta), magnet_d * sin(theta), -1])
      color([0, 1, 0])cylinder(h=magnet_h, d=magnet_d, $fn=50);
  }
}
