inch = 25.4;
W = 132.230;
MKY_R = 2;
WW = 35;
WL = 47;
WH = 2;

window_w = 30.;
window_l = 37.5;
window_fw = 35;
window_fl = 47;
module electronics(){
  translate([-8.5, 0, 0])rotate(a=-90, v=[0, 0, 1])import("all_but_display.stl");
  color([0, 0, 1])translate([-8.5, 0, 6])rotate(a=-90, v=[0, 0, 1])import("display.stl");
  translate([-8.7, -20.5, -1.8])rotate(a=-180, v=[1, 0, 0])rotate(a=-90, v=[0, 0, 1])import("power.stl");
}
module keepout(){
    hull(){
      translate([-18, -21 - .11*inch -3, 12+2.5+1])
	color([1, 0, 0])
	cube([WW, WL + 6, WH]);
      // left and right wings
      translate([0, 49.6, 16.5])cylinder(d=33, h=1);
      translate([0, -49.6, 16.5])cylinder(d=33, h=1);
      // pwr up
      translate([-34, 0, 16.5])cylinder(d=33.5, h=1);
      
      translate([-8.5, 0, 4.5])// was [-8.5, 0, 5]
	rotate(a=-90, v=[0, 0, 1])
	scale([1.05, 1.05, 9.65])import("board_OTS.stl");
    }
}
module xter(){
    minkowski(){
      keepout();
      sphere(r=1.6, $fn=20);
    }
}
module body(){
  difference(){
    xter();
    keepout();
  }
}

module drill()
{
  translate([0, 49.6, 0])cylinder(d=7, h=100);   // encoder
  translate([0, -49.6, 0])cylinder(d=7, h=100);  // encoder
  color([.4, .3, 0])translate([16.7, -10.25, 6.5]) 
    rotate(v=[0, 1, 0], a=90)
    cylinder(d1=1, d2=13, h=4);                    // power
  translate([0, -34, .5])cube([100, 11, 9]);     // usb
  translate([0, -32, 4])cube([140, 7, 2]);       // usb
  translate([-17, 30, -20])cylinder(r=3, h=20);     // ezkey pair
  color([.2, .5, .2])translate([-35, 0, -11.])
    cylinder(d=31, h=28); // power up button hole
  color([.2, .5, .2])translate([-35, 0, -11.])
    cylinder(d=29.5, h=40); // power up button hole

  translate([0, 49.6, -0])color([0, 1, 1])cylinder(h=25, d=16);
  translate([0, -49.6, -0])color([0, 1, 1])cylinder(h=25, d=16);

}

module encoder_shaft(){
  difference(){
    translate([0, 0, -1])
      cylinder(d=6.1, h=100, $fn=100);
    translate([1.5, .4, 0])rotate(a=-20, v=[0,0,1])cube([.6, 100, 100]);
    translate([1.5, -.4, 10])rotate(a=20, v=[0,0,1])
      rotate(a=180, v=[1, 0, 0])cube([.6, 100, 10]);
  }
}
module knob(){
  $fn=100;
  difference(){
    translate([0, 0, 0])color([0, 1, 1])cylinder(h=11, d=10);
    //thumb
    //translate([10, 0, 11])scale([1, 1, .5])sphere(d=12);
    encoder_shaft();
  }
  translate([0, 0, 8])
    minkowski(){
    difference(){
      sphere(r=2);
      translate([-50, -50, -100])cube([100, 100, 100]);
    }
    color([1, 0, 0])cylinder(h=2, d2=31.5, d1=32);
  }
}

module power_up(D = 33, d = 31, h = 19.2){// check these diameters!
  translate([-35, 0, 0]){
    cylinder(h=h, d=d);
    translate([0, 0, h])cylinder(h=1, d=D);
    color([1, 0, 0])translate([0, 0, h + 1])cylinder(h=2, d=d);
    translate([0, -5, -12.5])cube([1, 10, 12.5]);
  }
}
// translate([-35, 0, 0])power_up();
module knobs(){
  translate([0, 49.6, 14])knob();
  translate([0, -49.6, 14])knob();
}

module encoder_enclosures(){
  difference()
    {
      union(){
	color([1, 0, 0])translate([-35, 0, -11.5])hull()
	  { // power up
	    translate([4, 0, 0])cylinder(h=1, d=41);
	    //translate([0, 0, 29.5])cylinder(d=31.7, h=1);
	    translate([0, 0, 29.5])cylinder(d=34, h=.001);
	  }

      }
      {
	
	// color([.3, .1, .1])translate([-8.5, 0, 17])
	// hull() rotate(a=-90, v=[0, 0, 1]) scale([1, 1, 17])import("board_OTS.stl");
	//sphere(r=3);
      }
    }
}

module case(){
  difference(){
    union(){
      intersection(){
	screw_mounts();
	xter();
      }
      difference(){body();encoder_enclosures();}
      difference(){encoder_enclosures();keepout();}
      color([.3, .3, .3])
	translate([-30, 0, -11.4])
	rotate(a=180, v=[0, 1, 0])
	import("Garmin_Quarter_Turn_Plate.stl");
      translate([-30, 0, -13.9])cylinder(h=2.5, r1=16, r2=20);
      translate([5, -55, -11.5])difference(){
	sphere(r=6);
	translate([-7, -7, 0])cube(14);
      }
      translate([5, 55, -11.5])difference(){
	sphere(r=6);
	translate([-7, -7, 0])cube(14);
      }
    }
    drill();
    translate([-15, -9.5 - 12, 12])color([0, 0, 0])cube([window_w, window_l, WH+10]);
  }
}

module screw_mounts(){
  // bottom upper right
  h=8.4; // was 9.4
  color([1, 0, 0])
    difference(){
    translate([15., -37.45, -10.5])cylinder(h=h, $fn=6, r1=8, r2=4);
    //translate([15., -37.45, -13])cylinder(h=h, $fn=60, r=3);
    translate([15., -37.45, -12])cylinder(h=h+2, $fn=60, r=1.2);
  }
  y = 38.7;
  x = 15.8;
  color([1, 0, 0]) // bottom upper left
    difference(){
    translate([x, y, -11])cylinder(h=4.4, $fn=6, r1=8, r2=4); // was h=4.9
    translate([x, y, -11])cylinder(h=4.4+1, $fn=60, r=1.5);   // was h=4.9
  }
  translate([0, 0, 1])color([0, 1, 0]) // top upper left
  difference(){ 
    translate([x, y, 0])cylinder(h=20, $fn=6, r2=8, r1=4);
    translate([x, y, -1])cylinder(h=20+2, $fn=60, r=1.2);
  }
  yy = 45.7;
  xx = -20.3;
  hh = 8.9; // was 9.4
  color([1, 0, 0])
    difference(){
    translate([xx, yy, -11])cylinder(h=hh, $fn=6, r1=8, r2=4);
    translate([xx, yy, -12])cylinder(h=hh+2, $fn=60, r=1.5);
  }
  color([1, 0, 0])
    difference(){
    translate([xx, -yy, -11])cylinder(h=hh, $fn=6, r1=8, r2=4);
    translate([xx, -yy, -12])cylinder(h=hh+2, $fn=60, r=1.5);
  }
  color([0, 1, 0]) translate([0, 0, 1]) // top lower left
  difference(){
    translate([xx, yy, 0])cylinder(h=15, $fn=6, r2=8, r1=4);
    translate([xx, yy, -1])cylinder(h=15+2, $fn=60, r=1.2);
  }
  color([0, 1, 0]) translate([0, 0, 1])// top lower right
  difference(){
    translate([xx, -yy, 0])cylinder(h=15, $fn=6, r2=8, r1=4);
    translate([xx, -yy, -1])cylinder(h=15+2, $fn=60, r=1.2);
  }
  dx = 15;
  dy = 25.45;
  dz = 13.8+2 - .6;
  difference(){
    union(){
      for(j=[-1, 1]){
	for(i=[-1, 1]){
	  difference(){
	    translate([j * dx, i * dy, dz])cylinder(h = 5, d=8, $fn=6);
	    translate([j * dx, i * dy, dz-1])cylinder(h = 4, d=1.5, $fn=60);
	  }
	}
      }
    }
    translate([-window_fw/2, -window_fl/2, dz-5])cube([window_fw, window_fl, 100]);
  }
}

//knobs();
// top
module top(){
  difference(){
  case();
  translate([-500, -500, -1000 -1.6])cube(1000);
  // translate([-8.5, 0, 0])hull() rotate(a=-90, v=[0, 0, 1]) scale([1, 1, 17])import("board_OTS.stl");
  
  }
}

module bottom(){
  // bottom
  translate([0, 0, -20])
    difference(){
  case();
  translate([-500, -500, -1.6])cube(1000);
  // translate([-8.5, 0, 0])hull() rotate(a=-90, v=[0, 0, 1]) scale([1, 1, 17])import("board_OTS.stl");
  ///screws
  yy = 45.7;
  xx = -20.3;
  translate([xx, yy, -108])
    cylinder(h=100, d=6, $fn=40);
  translate([xx, -yy, -108])
    cylinder(h=100, d=6, $fn=40);
  y = 38.7;
  x = 15.8;
  translate([x, y, -108])
    cylinder(h=100, d=6, $fn=40);
  translate([x-.8, -y+1.2, -108])
    cylinder(h=100, d=6, $fn=40);
  }

}

//keepout();
//top();
bottom();
//knob();
// knobs();
//encoder_shaft();

// color([0, 0, 1])electronics();
//power_up();
// color([1, 0, 0])translate([0, 0, 0])cylinder(d=2, h=13);
//translate([10, 28, 16.6-1.4])cylinder(r=5, h=2.25);
