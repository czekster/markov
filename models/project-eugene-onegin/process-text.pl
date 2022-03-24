#!/usr/bin/perl

use strict;
use warnings;

if (@ARGV != 1) { 
   print "missing FILE parameter. \nusage: perl process-text.pl FILE\n";
   exit;
}

my $file = $ARGV[0];

open(INFILE, "<$file") or die("cannot open hash file named $file\n");
#open INFILE, '<:utf8', $file;
my(@lines) = <INFILE>;
close(INFILE);
my $vowels = 0;
my $consonants = 0;
my $chars = 0;
my $VV = 0; #vowel vowel
my $VC = 0; #vowel consonant
my $CV = 0; #consonant vowel
my $CC = 0; #consonant consonant
foreach my $line (@lines) {
   $line =~ s/\n//g;
   $line =~ s/^\s+//;  #trim at start
   $line =~ s/\s+$//;  #trim at end
   $line =~ s/\s+/ /g; #remove multiple spaces for single space
   next if (substr($line, 0, 1) eq '#');
   #print "line: ".$line."\n";
   for my $i (1 .. length $line) {
      my $char = substr($line, $i-1, 1);
      my $nextc = substr($line, $i, 1);
      if (is_vowel($char) && is_vowel($nextc)) { $VV++; }
      elsif(is_vowel($char) && !is_vowel($nextc)) { $VC++; }
      elsif(!is_vowel($char) && is_vowel($nextc)) { $CV++; }
      elsif(!is_vowel($char) && !is_vowel($nextc)) { $CC++; }
      #print "first $char then $nextc ";
      if (is_vowel($char)) { $vowels++; }
      else { $consonants++; }
      $chars++;
   }
   #print "\n";
   #exit;
}
print "VV: $VV\n";
print "VC: $VC\n";
print "CV: $CV\n";
print "CC: $CC\n";
print "Total: ".($VV+$VC+$CV+$CC)."\n";

print "\nVowels: ".$vowels."\n";
print "Consonants: ".$consonants."\n";
print "Characters: ".$chars."\n";


sub is_vowel {
   my ($ch) = @_;
   return ($ch eq 'a' || $ch eq 'e' || $ch eq 'i' || $ch eq 'o' || $ch eq 'u');
}

