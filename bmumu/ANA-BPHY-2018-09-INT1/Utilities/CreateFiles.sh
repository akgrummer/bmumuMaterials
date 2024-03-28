for a in Introduction AnalysisMethodology Samples MCTuning Preselection Trigger CutFlow MuonFakes BackgroundModeling ContinuumBDT DataMCComparison BPlusYield EfficiencyAndAcceptance SignalFit BranchingRatio 
do
    echo $a
    cat >> InternalNote_$a.tex <<EOF
\section{$a}
\label{sec:$a}

\clearpage
EOF
done


 
