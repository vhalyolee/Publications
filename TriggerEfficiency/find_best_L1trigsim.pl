#!/usr/bin/perl -w

use strict;

my $do_all_samples = 1;  # 1: use all mH points; 0: use mH=400 only
#my $file_format = "l1_trigsim_results/L1trigsimNew_4BScan_%s.txt";
my $file_format = "l1_trigsim_results/L1trigsimNewMET_4BScan_%s.txt";

my @samples;
if ($do_all_samples) {
    @samples = qw(H100X20C50 H100X20C100 H100X20C150 H100X20C200 H100X20C250 H100X20C300 H100X20C350 H100X20C400 H100X20C450 H100X20C500 H100X20C550 H100X20C600 H125X20C10 H125X20C20 H125X10C40 H125X20C50 H125X20C100 H125X20C150 H125X20C200 H125X20C250 H125X20C300 H125X20C350 H125X20C400 H125X20C40 H125X20C450 H125X20C500 H125X20C550 H125X20C600 H125X30C40 H125X40C40 H125X50C40 H125X60C40 H200X20C50 H200X20C100 H200X20C150 H200X20C200 H200X20C250 H200X20C300 H200X20C350 H200X20C400 H200X20C450 H200X20C500 H200X20C550 H200X20C600 H250X20C50 H250X20C100 H250X20C150 H250X20C200 H250X20C250 H250X20C300 H250X20C350 H250X20C400 H250X20C450 H250X20C500 H250X20C550 H250X20C600 H300X20C50 H300X20C100 H300X20C150 H300X20C200 H300X20C250 H300X20C300 H300X20C350 H300X20C400 H300X20C450 H300X20C500 H300X20C550 H300X20C600 H350X20C50 H350X20C100 H350X20C150 H350X20C200 H350X20C250 H350X20C300 H350X20C350 H350X20C400 H350X20C450 H350X20C500 H350X20C550 H350X20C600 H400X20C50 H400X20C100 H400X20C150 H400X20C200 H400X20C250 H400X20C300 H400X20C350 H400X20C400 H400X20C450 H400X20C500 H400X20C550 H400X20C600);
} else {
    @samples = qw(H400X20C50 H400X20C100 H400X20C150 H400X20C200 H400X20C250 H400X20C300 H400X20C350 H400X20C400 H400X20C450 H400X20C500 H400X20C550 H400X20C600);
}

my @relerr2;
my @abserr2;
my @results;

my %indices1j = ("92.0" => 0, "110.0" => 1, "128.0" => 2, "146.0" => 3, "164.0" => 4);
my %indices2j = ("40.0" => 0, "44.0" => 1, "48.0" => 2, "56.0" => 3, "64.0" => 4, "72.0" => 5);
my %indicesR = ("129.0" => 0, "154.0" => 1, "179.0" => 2, "237.0" => 3, "295.0" => 4);

my %simEffs;
my %trueEffs;

foreach my $sample (@samples) {
    my $iR;
    my $trueEff;
    
    $sample =~ /H(\d+)X(\d+)C(\d+)/;
    my $mh = $1;
    my $mx = $2;
    my $ct = $3;

    # Get the real trigger efficiency.
    open EFFFILE, "eff_results/eff_4BScan_${sample}.txt";
    while (my $effline = <EFFFILE>) {
	if ($effline =~ /AnyTriggerL1 *([\d.]+) *\+\/-/) {
	    $trueEff = $1;
	    last;
	}
    }
    close EFFFILE;

    # print $sample, " true eff = ", $trueEff, "\n";

    $trueEffs{"$mh,$mx,$ct"} = $trueEff;

    # Get the simulated efficiencies.
    open TRIGSIM, (sprintf $file_format, $sample);
    while (my $line = <TRIGSIM>) {
	if ($line =~ /R cut = ([0-9\.]+)/) { # formerly 1j cut
	    $iR = $indicesR{$1};
	} elsif ($line =~ /2j cut = ([0-9\.]+)/) {
	    my $i2j = $indices2j{$1};
	    my @fields = split(" ", $line);
	    for (my $imet=0; $imet<5; $imet++) {
		my $eff = $fields[5+4*$imet];
		# print " $iR $i2j $imet sim eff = $eff\n";
		my $relerr = ($trueEff == 0 ? 0 : ($eff-$trueEff)/$trueEff);
		my $abserr = ($eff-$trueEff);
		$relerr2[$iR][$i2j][$imet] += $relerr*$relerr;
		$abserr2[$iR][$i2j][$imet] += $abserr*$abserr;
		my $summary = "$sample $trueEff $eff (".sprintf("%.1f", abs($abserr)).") (".
		    sprintf("%.1f", abs($relerr*100))."%)\n";
		$results[$iR][$i2j][$imet] .= $summary;
		$simEffs{"$mh,$mx,$ct,$iR,$i2j,$imet"} = $eff;
	    }
	}
    } # line loop
    close TRIGSIM;
} # samples loop

# Now find the best one.
my $bestrelerr = 999999;
my $bestabserr = 999999;
my ($bestreli, $bestrelj, $bestrelk, $bestabsi, $bestabsj, $bestabsk);
for (my $i=0; $i<5; $i++) {
    for (my $j=0; $j<6; $j++) {
	for (my $k=0; $k<5; $k++) {
	    if ($relerr2[$i][$j][$k] < $bestrelerr) {
		$bestrelerr = $relerr2[$i][$j][$k];
		$bestreli = $i;
		$bestrelj = $j;
		$bestrelk = $k;
	    }
	    
	    if ($abserr2[$i][$j][$k] < $bestabserr) {
		$bestabserr = $abserr2[$i][$j][$k];
		$bestabsi = $i;
		$bestabsj = $j;
		$bestabsk = $k;
	    }
	}
    }
}

# Now print it out.
print "Best relative error is $bestreli $bestrelj $bestrelk = $bestrelerr\n";
print $results[$bestreli][$bestrelj][$bestrelk];
print "Best absolute error is $bestabsi $bestabsj $bestabsk = $bestabserr\n";
print $results[$bestabsi][$bestabsj][$bestabsk];

print "{";
foreach my $ct (50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600) {
    if ($do_all_samples) {
	print "{", $trueEffs{"125,20,$ct"}, ",", $simEffs{"125,20,$ct,$bestreli,$bestrelj,$bestrelk"}, ",";
    } else {
	print "{";
    }
    print $trueEffs{"400,20,$ct"}, ",", $simEffs{"400,20,$ct,$bestreli,$bestrelj,$bestrelk"}, "},\n";
}
print "}\n";
    

print "\n";
