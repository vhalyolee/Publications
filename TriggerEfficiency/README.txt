This directory contains the following:
 - Code for running the trigger efficiency (for real CMS triggers) on our samples
 - Code for running our trigger simulation (from gen-level) on our samples
 - Code for comparing the two
 - Code for running the L1 trigger simulation (from gen-level) on our samples.

The code in here is as follows:

* Running the trigger efficiency: To run the trigger efficiency on a sample, use one of the run scripts
  run_eff_4BScan_*.py. These are automatically generated from run_eff_ScanTemplate.py by
  make_runlists_scan.pl. (Alternatively, there exists make_runlists_scan_fullsim.pl to make the run scripts
  for the fullsim samples, or make_runlists_central.pl/run_eff_template_central.py to make the runlists for
  running on the central files.)

* Output: When the run scripts are run (run_all_jobs.sh is a simple script to automate this), the resulting
  output is stored in eff_4BScan_*.txt. These, along with the ROOT output files (not stored in the SVN
  archive), are stored in eff_results.

* Plotting scripts: extract_eff.pl will take the efficiencies from all of the text files and make a C snippet
  suitable for plotting. extract_eff_1d.pl and extract_eff_1d_mx.pl do the same, but only for the efficiency
  vs. ctau and efficiency vs. mx cases. The results are stored in efficiencies_2d.txt,
  efficiencies_1d_ctau.txt, and efficiencies_1d_mx.txt; the versions _syst.txt include the 15% systematic for
  the differences from simulation. PlotEff2D.C plots the 2D efficiency, while PlotEffVsMX.C and
  PlotEffVsCtau.C make the 1D plots. extract_leading_trigger.pl will print out the name of the best single
  trigger for each sample.

* Trigger simulator: The workflow for the trigger simulator is like the main efficiency scripts:
 - use make_runlists_trigsim.pl to make the run files, run_trigsim_4BScan*.py
 - run these run files; the output is in trigsim_results/trigsim_4BScan*.txt (currently there is "New6/7/8",
 which uses the new trigger simulation with a prompt track cut of 6/7/8).
 - use find_best_trigsim_new.pl to find the cuts that result in the most accurate simulation
 - plot using PlotEffTrigSimNew.C

* L1 trigger simulator: this is almost identical to the (HLT) trigger simulator above:
 - use make_runlists_L1trigsim.pl to build the run files, run_L1trigsim_4BScan*.py from the template
   run_L1trigsim_template.py
 - run these files (you can use run_all_L1trigsim.sh to do so); the output is in l1_trigsim_results

 - Note: there are a few different versions of the L1 trigger simulator. The first varied the single jet cut,
 the double jet cut, and the MET cut. This version of the simulator is saved in
 plugins/L1TriggerSimulator.cc.old and the results are in l1_trigsim_results/L1trigsim_4BScan_*. The second
 fixes the single jet cut but also varies the radius cut used to model jets leaving the calorimeter. The first
 results from this version are in l1_trigsim_results/L1trigsimNew_4BScan_*. Finally, the simulator was updated
 so that jets leaving the calorimeter would also be included in the MET. The results from this final version
 are l1_trigsim_results/L1trigsimNewMET_4BScan_*.

 - use find_best_L1trigsim.pl to find the cuts that result in the most accurate simulation
 - plot the results with PlotEffL1TrigSim.C. L1TriggerSim.png, L1TriggerSimNew.png, and L1TriggerSimNewest.png
 are the results from the three versions described above.

Finally, once you've picked a best HLT and L1 simulation, you can use extract_sim_eff.pl to obtain arrays of
the efficiency as a function of H and X mass suitable for plotting in ROOT. efficiencies_simulated.txt is the
output of this script.

* Prescale tools: In order to build a list of all unprescaled triggers we must know which triggers are
  unprescaled. Unfortunately, MC doesn't store the prescale factors so I have to get this information from
  data and then apply it to the trigger list in the MC samples.

  trigger_prescales_data.txt contains a list of triggers from a data sample. (I don't remember how the data
  sample was chosen -- it was an attempt to match the MC sample but not entirely successfully.) After
  "Prescale" is the prescale column, the total prescale (L1*HLT), the L1 prescale, and the HLT
  prescale. trigger_prescales_L1_data.txt is basically the same thing except with individual information about
  the L1 prescales but not the combined prescale information.

  Then, a list of triggers in the MC is built in trigger_list_mc_all.txt (all triggers) and
  trigger_list_mc_HLT.txt (HLT triggers only). The script find_prescales.pl is then used to match the triggers
  in the MC sample to the data sample (not always successfully, as not all of them match) and extract the
  resulting prescale for the triggers in the MC sample. This produces HLT_prescales.txt. Finally, one uses
  this to produce unprescaled_HLT_triggers.txt and, after removing a few obviously not useful triggers (AlCa
  and the like), unprescaled_HLT_triggers_clean.txt. unprescaled_L1_triggers.txt is also built (much more
  easily, since here we don't have to worry about version numbers).

  When we generated the new samples, they of course had a different trigger menu, so this required updating
  the list of unprescaled triggers. This is accomplished by update_version_numbers.pl, which takes the old
  list of unprescaled triggers, the list of triggers from the new MC sample (trigger_list_mc_new.txt) and
  produces a new list of unprescaled triggers (unprescaled_HLT_triggers_mcnew.txt).

* Efficiency plots: The efficiency_plots directory contains some more scripts for plotting trigger
  efficiencies from the ROOT output files. Hopefully they are pretty self-explanatory.
