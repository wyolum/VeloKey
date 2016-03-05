inch = 25.4;
W = 132.230;
MKY_R = 2;
W_W = 35;
W_L = 47;
W_H = 2;

translate([-8.5, 0, 0])rotate(a=-90, v=[0, 0, 1])import("all_but_display.stl");
translate([-8.5, 0, 9])rotate(a=-90, v=[0, 0, 1])import("display.stl");
//translate([-18, -21 - .11*inch, 17.7])color([0, 0, 0])cube([W_W, W_L, W_H]);

translate([-8.5, -20.5, -1.8])rotate(a=-180, v=[1, 0, 0])rotate(a=-90, v=[0, 0, 1])import("power.stl");
module drill()
{
  translate([0, 49.6, 0])cylinder(d=7, h=100);   // encoder
  translate([0, -49.6, 0])cylinder(d=7, h=100);  // encoder
  color([1, 0, 0])translate([0, -10.25, 5.5]) 
    rotate(v=[0, 1, 0], a=90)
    cylinder(d=7, h=100);                        // reset
  translate([0, -34, .5])cube([100, 11, 9]);     // usb
  translate([0, -32, 4])cube([140, 7, 2]);       // usb
}
//drill();

module knob(){
  translate([0, 0, 0])color([0, 1, 1])cylinder(h=11, d=8);
  translate([0, 0, 8])
    difference(){
    intersection()
      {
	color([0, 0, 1])cylinder(h=3, d=34);
	cylinder(d1 = 34, d2=33, h=6);
      }
    translate([0, 0, -1])scale([1, 1, .18])sphere(d=33);
    translate([10, 0, 4])scale([1, 1, .25])sphere(d=14);
  }
}

module power_up(D = 33, d = 31, h = 19.2){// check these diameters!
  cylinder(h=h, d=d);
  translate([0, 0, h])cylinder(h=1, d=D);
  color([1, 0, 0])translate([0, 0, h + 1])cylinder(h=2, d=d);
  translate([0, -5, -12.5])cube([1, 10, 12.5]);
}

module knobs(){
  translate([0, 49.6, 14])knob();
  translate([0, -49.6, 14])knob();
}
knobs();

module z_profile(){
  hull(){
    translate([-8.5, 0, 50])
      rotate(a=-90, v=[0, 0, 1])
      hull()scale([1, 1, 100])
      import("board_OTS.stl");
    translate([-45, 0, -50])cylinder(d=34, h=100);
  }
}

color([.1, .2, .3])
intersection(){
  difference(){
    union(){
      color([1, 1, 0])translate([0, -49.6, 18])scale([1, 1, .19])sphere(d=43);
      color([1, 1, 0])translate([0,  49.6, 18])scale([1, 1, .19])sphere(d=43);

      translate([-100, -75, 17.7+2])cube([200, 150, 1]);
      // display screw mounts
      for(dy = [0, -2*inch]){
	for(dx = [0, 1.15*inch]){
	  difference(){
	    x = -15 + dx; 
	    y = 1*inch  + dy;
	    z = 17.5;
	    color([1, 0, 0])
	      translate([x, y, z])cylinder(h = 2, d=.4*inch, $fn=6);
	    translate([x, y, z-1])cylinder(h = .3*inch+2, d=.06*inch, $fn=6);
	  }
	}
      }
    }
    translate([-18, -21 - .11*inch, 17.7 - 5])color([1, 1, 1])cube([W_W, W_L, 10]);
  }
  z_profile();
}
translate([-40, 0, 1.8])power_up();
color([.1, .1, .1])translate([-35, 0, -11])
rotate(a=180, v=[0, 1, 0])
import("Garmin_Quarter_Turn_Plate.stl");
translate([-8.5, 0, -10])
rotate(a=-90, v=[0, 0, 1])
hull()
import("board_OTS.stl");


