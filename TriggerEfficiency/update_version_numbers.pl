#!/usr/bin/perl -w

# This is a simple script which takes the list of unprescaled triggers from an existing file,
# a list of triggers from a new file with different version numbers, and produces a list
# of unprescaled triggers in that new file.

use strict;

open OLDTRIGS, "unprescaled_HLT_triggers_clean.txt" or die "Couldn't open old_triggers.txt: $!\n";
open NEWTRIGS, "trigger_list_mc_new.txt" or die "Couldn't open new trigger input file: $!\n";
open OUTFILE, ">unprescaled_HLT_triggers_mcnew.txt" or die "Couldn't open output trigger list: $!\n";

my @newtrigs = <NEWTRIGS>;

foreach my $line (<OLDTRIGS>) {
    $line =~ /\"(.*_v)(\d+)\"/;
    my $trigname = $1;
    my $trigfull = $1.$2;
    
    my @matchtrig = grep /$trigname/, @newtrigs;
    
    if (@matchtrig == 0) {
	warn "Failed to find $trigname\n";
    } elsif (@matchtrig > 1) {
	die "Found too many matches for $trigname\n";
    } else {
	my $matchname = $matchtrig[0];
	$matchname =~ /($trigname\d+)/;
	my $newtrig = $1;
	#print "$trigfull -> $newtrig\n";
	print OUTFILE "\"$newtrig\",\n";
    }
}
