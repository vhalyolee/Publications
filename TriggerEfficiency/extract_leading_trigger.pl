#!/usr/bin/perl -w

# A simple script to extract the efficiency values from the text
# files output by the analyzer script and put them in arrays suitable
# for plotting in ROOT.

use strict;

my @mh_vals = (100, 125, 200, 250, 300, 350, 400);
my $mx = 20;
my @ct_vals = (# 10, 20, 40, 
	       50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600);
my @trigs = ("AnyDisplacedTriggerL1", "AnyTriggerL1", "AnyDisplacedTriggerHLT", "AnyTriggerHLT",
	     "BestTriggerHLT");
my @individual_trigs = ('HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v\d+',
			'HLT_DoubleDisplacedMu4_DiPFJet40Neutral_v\d+',
			'HLT_L2TripleMu10_0_0_NoVertex_PFJet40Neutral_v\d+',
			'HLT_HT300_DoubleDisplacedPFJet60_v\d+',
			'HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v\d+');
my $ntrigs = scalar(@trigs);


my $effvals = "float eff_all[nmh][nctau][ntrigs] = {\n";
my $efferrs = "float efferr_all[nmh][nctau][ntrigs] = {\n";
foreach my $mh (@mh_vals) {
    $effvals .= "// mH=$mh\n{\n";
    $efferrs .= "// mH=$mh\n{\n";
    
    foreach my $ct (@ct_vals) {
	my $infile = "eff_results/eff_4BScan_H${mh}X${mx}C${ct}.txt";
	open INFILE, $infile or die "Couldn't open $infile: $!\n";

	my @found_effvals;
	my @found_efferrs;

	my $best_eff = 0;
	my $best_err = 0;
	my $best_name = "None";

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
		if ($line =~ /($trig) +([0-9.]+) +\+\/- ([0-9.]+)/) {
		    if ($2 > $best_eff) {
			$best_eff = $2;
			$best_err = $3;
			$best_name = $1;
		    }
		}
	    }
	} # loop over input lines
	$found_effvals[4] = $best_eff;
	$found_efferrs[4] = $best_err;

	print "mh=$mh mx=$mx ct=$ct best single trigger = $best_name\n";

	if (scalar(@found_effvals) != $ntrigs) {
	    die "Failed to find all target triggers in $infile!\n";
	}

	$effvals .= "{" . join(", ", @found_effvals) . "}, // ctau=$ct\n";
	$efferrs .= "{" . join(", ", @found_efferrs) . "}, // ctau=$ct\n";
    }
    $effvals .= "},\n";
    $efferrs .= "},\n";
}
    

