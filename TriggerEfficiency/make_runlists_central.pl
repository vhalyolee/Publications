#!/usr/bin/perl -w

use strict;

my @dirs = glob("/pnfs/cms/WAX/11/store/mc/Summer12_DR53X/HTo2LongLivedTo4B*");

foreach my $dir (@dirs) {
    my $finaldir;
    if (-e "$dir/AODSIM/PU_S10_START53_V7C-v2/") {
	$finaldir = "$dir/AODSIM/PU_S10_START53_V7C-v2/10000";
    } else {
	$finaldir = "$dir/AODSIM/PU_S10_START53_V7C-v1/10000";
    }
    my @files = glob("$finaldir/*.root");

    $dir =~ /HTo2LongLivedTo(4B)_.*_MH-(\d+)[_-]MFF-(\d+)/;
    my $tag = "${1}_H${2}X${3}";
    print $tag, " ";
    open INFILE, "run_eff_template_central.py";
    open OUTFILE, ">run_eff_${tag}.py";
    
    while (my $line = <INFILE>) {
	$line =~ s/TAG/$tag/;
	if ($line =~ /FILENAMES/) {
	    # print file list
	    foreach my $file (@files) {
		$file =~ s^/pnfs/cms/WAX/11^^g;
		print OUTFILE "\"$file\",\n";
	    }

	} else {
	    print OUTFILE $line;
	}
    } # line loop
    close INFILE;
    close OUTFILE;
}
print "\n";
