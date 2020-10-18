// basic enclosure
$fn = 60;

width = 40;   // x
length = 40;  // y
height = 20;  // z
cornerRadius = 4;
wallThickness = 4;

// main enclosure
translate([0,0,height/2]){
  difference(){
    roundedBox(length, width, height, cornerRadius); 

    // cut off top
    translate([0,0,1]){
      roundedBox(length-wallThickness, width-wallThickness, height-1, cornerRadius); 
    }

    // cut out OLED slot
    translate([width/2,0,0]){
      cube([10,15,10], center=true);
    }
  }
}

// lid
// translate([width*2,10,0]){
//   roundedBox(length, width, 1, cornerRadius);

//   // hollow out
//   difference() {
//     translate([1,1,0]){
//       roundedBox(length-2, width-2, 4, cornerRadius);
//     }
//     translate([2,2,0]){
//       roundedBox(length-4, width-4, 6, cornerRadius);
//     }    
//   }
// }

// base slab to work with
module roundedBox(length, width, height, radius){
  dRadius = 2 * radius;

  minkowski(){
    cube(size=[width-dRadius, length-dRadius, height], center=true);
    cylinder(r=radius, h=0.01, center=true);
  }
}