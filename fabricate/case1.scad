inch = 25.4;
W = 132.230;
MKY_R = 2;

inf = 200;
D_W = 47;
D_L = 35;
D_H = 10;
W_W = 38;
W_L = 31;
W_H = inf;

module screw_mount(h1, h2, side="bottom"){
  if(side == "bottom"){
    intersection(){
      color([1, 0, 0])difference(){
	cylinder(r1=8, r2 = 5, h=h1, $fn=6);
	translate([0, 0, -1])cylinder(r1=3, h=h1-2, $fn=30);
	translate([0, 0, -1])cylinder(r=1.6, h=h1 + 2, $fn=30);
      }
    }
  }
  else{
    color([0, 1, 0])difference(){
      translate([0, 0, h1 + 10])cylinder(r1=5., r2=8, h=h2, $fn=6);
      translate([0, 0, h1 - 1 + 10])cylinder(r=1.2, h=h2 + 2, $fn=30);  
    }
  }
}

module internal_space(){
  color([.5, .4, .5])intersection()
    {

      rotate(v=[1, 0, 0], a=90)
	linear_extrude(height = 400, center = true, convexity = 10)
	import (file = "proto1/side.dxf");
      color([0, 1, 0])
	translate([0, -W/2, 0]) 
	rotate(v=[0, 0, 1], a=90)rotate(a=90, v=[1, 0, 0])
	linear_extrude(height = 500, center = true, convexity = 10)
	import (file = "proto1/front.dxf");
      hull(){ // top outline
	translate([52, 49.6, 0])cylinder(d=35, h=100);
	translate([52, -49.6, 0])cylinder(d=35, h=100);
	translate([17, 0, 0])cylinder(d=34, h=100);
      }
      
    }
}

module my_solid(side="top"){ // "case" was taken
  intersection(){
    if(side=="top"){
      translate([-500, -500, + 30])cube([1000, 1000, 40]);       // top only
    }
    else{
      translate([-500, -500, -40 + 30])cube([1000, 1000, 40]); // bottom only
    }
    translate([MKY_R/2, 0, MKY_R/2])
      difference(){
      union(){
	minkowski(){
	  sphere(r=MKY_R);
	  internal_space();
	}
	if(side=="bottom"){
	  color([.5, .5, .5])
	    translate([17, 0, 2])
	    rotate(a=180, v=[0, 1, 0])
	    import("Garmin_Quarter_Turn_Plate.stl");
	}
      }
      // add shelf to internal space for electronics
      difference(){
      internal_space();
      // translate([-100, -100, 17.4])cube([200, 200, 1.5]);
      } 
    }
  }
}

module my_case(side="top"){
  difference(){
    union(){
      my_solid(side);
      if(side=="top"){
	// power up button support
	translate([16 + MKY_R, 0, 35.82-2.])cylinder(d=34, h=3); 
	// display support support
	translate([-1, -1, 8])
	translate([34.8 + MKY_R, -W_W/2, 35.82])
	  translate([(W_L - D_L)/2, W_W- D_W + 7.5,-D_H + 1])
	  cube([D_L + 2, D_W + 2, 2]);
	
      }
    }
    // display window
    translate([34.8 + MKY_R, -W_W/2, 35.82])
      union(){
      translate([(W_L - D_L)/2, W_W- D_W + 7.5,-D_H + 1])cube([D_L, D_W, D_H]);
      translate([0, 0, -0])cube([W_L, W_W, inf]);
    }
    translate([16 + MKY_R, 0, 1])
      cylinder(d=31, h=inf); // power up button hole
    translate([51, 49.6, 30])
      cylinder(d=.35*inch, h=inf, $fn=20); // encoder hole
    translate([51, -49.6, 30])
      cylinder(d=.35*inch, h=inf, $fn=20); // encoder hole
  }
}

module rim(){
  color([0, 1, 0])difference(){
    scale([1.0, 1.0, 1])translate([MKY_R/2, 0, MKY_R/2])internal_space();
    translate([1., 0, 0])scale([.98, .98, 1.05])translate([MKY_R/2, 0, MKY_R/2])internal_space();
    translate([-500, -500, 31])cube([1000, 1000, 10]);  
    translate([-500, -500, 0])cube([1000, 1000, 28]);  
  }
}

module screw_mounts(){
  intersection(){
    translate([MKY_R/2, 0, MKY_R/2])
    minkowski(){
      sphere(r=MKY_R);
      internal_space();
    }
    union(){
      translate([20, -22, 0])screw_mount(h1=30, h2=7.5, side="bottom");
      translate([20, 22, 0])screw_mount(h1=30, h2=7.5, side="bottom");
    }
  }
  union(){
    translate([20, -22, 0])screw_mount(h1=30, h2=7.5, side="top");
    translate([20, 22, 0])screw_mount(h1=30, h2=7.5, side="top");
  }
}
module shebang(){
  translate([0, 0, 10]) my_case("top");
  difference(){
    union(){
      my_case("bottom"); 
      rim();
    }
    translate([20, -22, 0])cylinder(h=50, r=3, $fn=50);
    translate([20, 22, 0])cylinder(h=50, r=3, $fn=50);
  }
}

shebang();
screw_mounts();




