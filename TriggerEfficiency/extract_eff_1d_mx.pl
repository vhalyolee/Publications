#!/usr/bin/perl -w

# A simple script to extract the efficiency values from the text
# files output by the analyzer script and put them in arrays suitable
# for plotting in ROOT.

use strict;

my $mh = 125;
my @mx_vals = (10, 20, 30, 40, 50, 60);
my $ct = 40;
my @trigs = ("AnyDisplacedTriggerL1", "AnyTriggerL1", "AnyDisplacedTriggerHLT", "AnyTriggerHLT",
	     "BestTriggerHLT");
my @individual_trigs = ('HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v\d+',
			'HLT_DoubleDisplacedMu4_DiPFJet40Neutral_v\d+',
			'HLT_L2TripleMu10_0_0_NoVertex_PFJet40Neutral_v\d+',
			'HLT_HT300_DoubleDisplacedPFJet60_v\d+',
			'HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v\d+');
my $ntrigs = scalar(@trigs);

print "const int nmx = ", scalar(@mx_vals), ";\n";
print "const int ntrigs = ", $ntrigs, ";\n";

my $effvals = "float eff_all[nmx][ntrigs] = {\n";
my $efferrs = "float efferr_all[nmx][ntrigs] = {\n";
    
foreach my $mx (@mx_vals) {
    my $infile = "eff_results/eff_4BScan_H${mh}X${mx}C${ct}.txt";
    open INFILE, $infile or die "Couldn't open $infile: $!\n";
    
    my @found_effvals;
    my @found_efferrs;
    
    my $best_eff = 0;
    my $best_err = 0;
    
    while (my $line = <INFILE>) {
	for (my $i=0; $i<@trigs; $i++) {
	    my $trig = $trigs[$i];
	    if ($line =~ /$trig +([0-9.]+) +\+\/- ([0-9.]+)/) {
		$found_effvals[$i] = $1;
		$found_efferrs[$i] = $2;
	    }
	}
	
	# Also look for best individual
	for (my $i=0; $i<@individual_trigs; $i++) {
	    my $trig = $individual_trigs[$i];
	    if ($line =~ /$trig +([0-9.]+) +\+\/- ([0-9.]+)/) {
		if ($1 > $best_eff) {
		    $best_eff = $1;
		    $best_err = $2;
		}
	    }
	}
    } # loop over input lines
    $found_effvals[4] = $best_eff;
    $found_efferrs[4] = $best_err;
    
    if (scalar(@found_effvals) != $ntrigs) {
	die "Failed to find all target triggers in $infile!\n";
    }

    # Add effect of systematic uncertainty
    for (my $i=4; $i<@found_efferrs; $i++) {
	my $staterr = $found_efferrs[$i];
	my $systerr = 0.15*$found_effvals[$i];
	$found_efferrs[$i] = sprintf("%.2f", sqrt($staterr*$staterr + $systerr*$systerr));
    }
    
    $effvals .= "{" . join(", ", @found_effvals) . "}, // mX=$mx\n";
    $efferrs .= "{" . join(", ", @found_efferrs) . "}, // mX=$mx\n";
}

print "\n// efficiency vs. ctau, mH = $mh, ctau = $ct mm\n";
print $effvals, "};\n";

print "\n// uncertainty on efficiency\n";
print $efferrs, "};\n";
    
