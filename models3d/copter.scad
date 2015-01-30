
module arm () {
	rotate([90, 0,,0]) {
		translate([0, 0, -112.5]) {
			cylinder(225, r=8, center=true);
		}
	}
	translate([0, 225, 0]) {
		cylinder(20, r=12, center=true);
	}
	translate([0, 225, 20]) {
		cylinder(20, r=11, center=true);
	}
	translate([0, 225, 30]) {
		cylinder(20, r=3, center=true);
	}
	translate([0, 225, 35]) {
		translate([42, 0, 0]) {
			rotate([-27, 0, 0]) {
				scale([1, 0.2, 1]) {
					cylinder(2, r=45, center=true);
				}
			}
		}
		translate([-42, 0, 0]) {
			rotate([27, 0, 0]) {
				scale([1, 0.2, 1]) {
					cylinder(2, r=45, center=true);
				}
			}
		}
	}
}

module copter (n=4) {
	cylinder(20, r=45, center=true);
	hull() {
		translate([0, 0,,30]) {
			cube([72, 72, 1], center=true);
		}
		translate([0, 0,,40]) {
			cube([46, 46, 1], center=true);
		}
	}
	translate([0, 0,,42]) {
		cube([26, 26, 5], center=true);
	}
	translate([20, 20,,17]) {
		cylinder(50, r=2, center=true);
	}
	translate([-20, 20,,17]) {
		cylinder(50, r=2, center=true);
	}
	translate([20, -20,,17]) {
		cylinder(50, r=2, center=true);
	}
	translate([-20, -20,,17]) {
		cylinder(50, r=2, center=true);
	}
	step = 360 / n;
	for (i = [0:step:360-step ]) {
		rotate([0, 0, i + step/2]) {
			arm ();
		}
	}
}

copter(4);


