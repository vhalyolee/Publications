#!/usr/bin/perl -w

# A simple script to extract the efficiency values from the text files
# from the trigsim output and put them into arrays suitable for plotting
# in ROOT.

use strict;

# Coordinates of the best L1 trigsim to pick.
my @best_l1_trigsim = (0, 0, 2);

# Coordinates of the best HLT trigsim to pick.
my @best_hlt_trigsim = (0, 0, 4);

my @samples = qw(H100X20C50 H100X20C100 H100X20C150 H100X20C200 H100X20C250 H100X20C300 H100X20C350 H100X20C400 H100X20C450 H100X20C500 H100X20C550 H100X20C600 H125X20C10 H125X20C20 H125X10C40 H125X20C50 H125X20C100 H125X20C150 H125X20C200 H125X20C250 H125X20C300 H125X20C350 H125X20C400 H125X20C40 H125X20C450 H125X20C500 H125X20C550 H125X20C600 H125X30C40 H125X40C40 H125X50C40 H125X60C40 H200X20C50 H200X20C100 H200X20C150 H200X20C200 H200X20C250 H200X20C300 H200X20C350 H200X20C400 H200X20C450 H200X20C500 H200X20C550 H200X20C600 H250X20C50 H250X20C100 H250X20C150 H250X20C200 H250X20C250 H250X20C300 H250X20C350 H250X20C400 H250X20C450 H250X20C500 H250X20C550 H250X20C600 H300X20C50 H300X20C100 H300X20C150 H300X20C200 H300X20C250 H300X20C300 H300X20C350 H300X20C400 H300X20C450 H300X20C500 H300X20C550 H300X20C600 H350X20C50 H350X20C100 H350X20C150 H350X20C200 H350X20C250 H350X20C300 H350X20C350 H350X20C400 H350X20C450 H350X20C500 H350X20C550 H350X20C600 H400X20C50 H400X20C100 H400X20C150 H400X20C200 H400X20C250 H400X20C300 H400X20C350 H400X20C400 H400X20C450 H400X20C500 H400X20C550 H400X20C600);

# Extract L1 efficiencies.
my $l1_file_format = "l1_trigsim_results/L1trigsimNewMET_4BScan_%s.txt";
my %indices1j = ("92.0" => 0, "110.0" => 1, "128.0" => 2, "146.0" => 3, "164.0" => 4);
my %indices2j = ("40.0" => 0, "44.0" => 1, "48.0" => 2, "56.0" => 3, "64.0" => 4, "72.0" => 5);
my %indicesR = ("129.0" => 0, "154.0" => 1, "179.0" => 2, "237.0" => 3, "295.0" => 4);

my %l1Eff;
my %l1Err;
my %hltEff;
my %hltErr;

foreach my $sample (@samples) {
    my $iR;
    my $iht;
    
    # Extract the L1 trigger efficiency from the L1 files.
    open L1TRIGSIM, (sprintf $l1_file_format, $sample);
    while (my $line = <L1TRIGSIM>) {
	if ($line =~ /R cut = ([0-9\.]+)/) {
	    $iR = $indicesR{$1};
	} elsif ($line =~ /2j cut = ([0-9\.]+)/) {
	    my $i2j = $indices2j{$1};
	    my @fields = split(" ", $line);

	    if ($iR == $best_l1_trigsim[0] &&
		$i2j == $best_l1_trigsim[1]) {
		
		# If this is the one that we've determined as the best L1
		# trigger, save it in the results.
		
		my $imet = $best_l1_trigsim[2];
		
		my $eff = $fields[5+4*$imet];
		my $statErr = $fields[7+4*$imet];

		# For MH<200, the systematic error is 20%. For MH>=200, 5% will
		# suffice.
		my $systErr;
		if ($sample =~ /H1/) {
		    $systErr = 0.20*$eff;
		} else {
		    $systErr = 0.05*$eff;
		}
		my $totErr = sprintf("%.2f", sqrt($statErr*$statErr + $systErr*$systErr));
		
		$l1Eff{$sample} = $eff;
		$l1Err{$sample} = $totErr;
	    }
	}
    } # line loop
    close L1TRIGSIM;

    # Now same deal for the HLT trigsim.
    open HLTTRIGSIM, "trigsim_results/trigsimNew8_4BScan_${sample}.txt";
    while (my $line = <HLTTRIGSIM>) {
	if ($line =~ /ht cut value (\d+)/) {
	    $iht = $1;
	} elsif ($line =~ /pt cut value (\d+)/) {
	    my $ipt = $1;
	    my @fields = split(" ", $line);

	    if ($iht == $best_hlt_trigsim[0] &&
		$ipt == $best_hlt_trigsim[1]) {

		my $idisp = $best_hlt_trigsim[2];
		
		my $eff = $fields[5+4*$idisp];
		my $statErr = $fields[7+4*$idisp];
		# Add 15% systematic error too.
		my $systErr = 0.15*$eff;
		my $totErr = sprintf("%.2f", sqrt($statErr*$statErr + $systErr*$systErr));
		
		$hltEff{$sample} = $eff;
		$hltErr{$sample} = $totErr;
	    }
	}
    } # line loop
    close HLTTRIGSIM;
    
} # samples loop

# Now print it all out.

my @mh_vals = (100, 125, 200, 250, 300, 350, 400);
my @mx_vals = (10, 20, 30, 40, 50, 60);
my $single_mh = 125;
my $single_ctau = 40;
my $single_mx = 20;
my @ct_vals_2d = (50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600);
my @ct_vals_1d = (10, 20, 40, @ct_vals_2d);
my $ntrigs = 2;

print "const int nmh = ", scalar(@mh_vals), ";\n";
print "const int nmx = ", scalar(@mx_vals), ";\n";
print "const int nctau_1d = ", scalar(@ct_vals_1d), ";\n";
print "const int nctau_2d = ", scalar(@ct_vals_2d), ";\n";
print "const int ntrigs = ", $ntrigs, ";\n";

# First, 2D.

my $effvals_2d = "float eff_2d_all[nmh][nctau_2d][ntrigs] = {\n";
my $efferrs_2d = "float efferr_2d_all[nmh][nctau_2d][ntrigs] = {\n";
foreach my $mh (@mh_vals) {
    $effvals_2d .= "// mH=$mh\n{\n";
    $efferrs_2d .= "// mH=$mh\n{\n";
    
    foreach my $ct (@ct_vals_2d) {
	my $sampleName = "H${mh}X${single_mx}C${ct}";

	$effvals_2d .= "{".$l1Eff{$sampleName}.", ".$hltEff{$sampleName}."}, // ctau = $ct mm\n";
	$efferrs_2d .= "{".$l1Err{$sampleName}.", ".$hltErr{$sampleName}."}, // ctau = $ct mm\n";
    }
    $effvals_2d .= "},\n";
    $efferrs_2d .= "},\n";
}

print "// efficiency vs. mH and ctau, mX = $single_mx GeV\n";
print $effvals_2d, "\n};\n";

print "// uncertainty on efficiency\n";
print $efferrs_2d, "\n};\n\n";

# Next, 1D vs. ctau.

my $effvals_1d_ct = "float eff_1d_ct[nctau_1d][ntrigs] = {\n";
my $efferrs_1d_ct = "float efferr_1d_ct[nctau_1d][ntrigs] = {\n";
foreach my $ct (@ct_vals_1d) {
    my $sampleName = "H${single_mh}X${single_mx}C${ct}";
    
    $effvals_1d_ct .= "{".$l1Eff{$sampleName}.", ".$hltEff{$sampleName}."}, // ctau = $ct mm\n";
    $efferrs_1d_ct .= "{".$l1Err{$sampleName}.", ".$hltErr{$sampleName}."}, // ctau = $ct mm\n";
}

print "// efficiency vs. ctau only, mH = $single_mh, mX = $single_mx GeV\n";
print $effvals_1d_ct, "};\n";

print "// uncertainty on efficiency\n";
print $efferrs_1d_ct, "};\n\n";

# Finally, 1D vs. mx.

my $effvals_1d_mx = "float eff_1d_mx[nmx][ntrigs] = {\n";
my $efferrs_1d_mx = "float efferr_1d_mx[nmx][ntrigs] = {\n";
foreach my $mx (@mx_vals) {
    my $sampleName = "H${single_mh}X${mx}C${single_ctau}";
    
    $effvals_1d_mx .= "{".$l1Eff{$sampleName}.", ".$hltEff{$sampleName}."}, // mX = $mx GeV\n";
    $efferrs_1d_mx .= "{".$l1Err{$sampleName}.", ".$hltErr{$sampleName}."}, // mX = $mx GeV\n";
}

print "// efficiency vs. mX only, mH = $single_mh GeV, ctau = $single_ctau mm\n";
print $effvals_1d_mx, "};\n";

print "// uncertainty on efficiency\n";
print $efferrs_1d_mx, "};\n";


