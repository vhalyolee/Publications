#!/usr/bin/perl -w

use strict;

open INFILE, "trigger_list_mc_HLT.txt" or die "Couldn't open trigger list: $!\n";
open OUTFILE, ">HLT_prescales.txt" or die "Couldn't open output file: $!\n";
open PRESCALES, "trigger_prescales_data.txt" or die "Couldn't open prescale file: $!\n";

my @prescales = <PRESCALES>;

foreach my $line (<INFILE>) {
    chomp $line;
    my $trigger = $line;
    $trigger =~ s/\d+$//;
    print "Looking for $trigger...\n";

    my @triggers = grep (/$trigger/, @prescales);
    my $prescale;
    if (@triggers > 1) {
	die "Multiple matches found, eep!\n";
    } elsif (@triggers == 0) {
	print "No match found for $trigger\n";
	$prescale = 0;
    } else {
	# Fields are: column, total prescale, L1 prescale, HLT prescale -- use as appropriate
	$triggers[0] =~ /Prescale: \d+ (\d+) -?\d+ \d+/;
	$prescale = $1;
    }
    print OUTFILE "$prescale $line\n";
}

