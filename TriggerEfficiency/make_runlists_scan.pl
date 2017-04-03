#!/usr/bin/perl -w

use strict;

my @dirs = glob("/eos/uscms/store/user/plujan/HTo2LongLived/*");

foreach my $dir (@dirs) {
    next if ($dir !~ /4BScan/);
    next if ($dir =~ /fullsim/);
    $dir =~ /(4BScan)_MH_(\d+)_MFF_(\d+)_CTau(\d+)/;
    my @files = glob("$dir/*.root");
    my $tag = "${1}_H${2}X${3}C${4}";
    print $tag, " ";
    open INFILE, "run_eff_ScanTemplate.py";
    open OUTFILE, ">run_eff_${tag}.py";
    
    while (my $line = <INFILE>) {
	$line =~ s/TAG/$tag/;
	if ($line =~ /FILENAMES/) {
	    # print file list
	    foreach my $file (@files) {
		# $file =~ s^/pnfs/cms/WAX/11^^g;
		$file =~ s^/eos/uscms^^g;
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
