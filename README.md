# bitsofcotton/p1
Generic predictor on \[- 1, 1\[-register consisted one function computed streams (up to aleph_0).

# How to use:
    std::vector<SimpleVector<double> > input;
    ...
      SimpleVector<double> resv(pRS0<double, 0>(input));

# How to use (command line):
    ./p1(-(32|64))? <line>? <step>? < data.txt
    # line == 0 to use whole input stream to predict next step.
    # 0 < line : number of back lines the predictor uses.

# Tips
Whole important tips is implanted into lieonn.hh as a comment.

# Another Download Sites (Leave)
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

# Leave
2023/02/28
2023/03/09 bug fix after close #1
2023/03/13 integrate all files into lieonn.hh after close #2
2023/03/24 code clean, after close #3.
2023/03/31 merge prand.
2023/04/02 merge catg fix.
2023/04/03 merge.
2023/04/05 fix makeProgramInvariant scale accuracy stability.
2023/04/21 make/revert ProgramInvariant algorithm change.
2023/06/24 fix to avoid observation matters.
2023/07/07 update the .cc comment.
2023/07/08 invariant cause +1, ok.
2023/10/30 update readme. copy structure reliably with randtools meaning.
2024/03/25 P1I to P01 change.
2024/04/09 add some of the tips.
2024/04/18 update readme.
2024/05/06 bitsofcotton/p0:p0.cc argv\[1\]\<0 case integrated into p1.cc.
2024/05/31 compile jammer.
2024/06/01 fix JAM.
2024/06/02 JAM into p2/cr.py.
2024/06/05 merge latest lieonn.hh.
2024/06/07 update readme.
2024/06/15 add progression.
2024/06/16 add progression \<0 argv.
2024/06/17 fix progression.
2024/06/19 merge latest lieonn.
2024/06/21 merge latest lieonn. INCLUDES command line argument change.
2024/06/22 update readme, p01 fatal fix. make/revert program invariants change friendly to predictors.
2024/06/23 large change around class instance initializer, also have progression short range fix.
2024/06/23 fatal fix around last update.
2024/06/24 fix addp == true progression case.
2024/06/26 fix Ppersistent.
2024/06/30 merge latest lieonn, update readme, leave with this.
2024/07/06 merge latest lieonn, update readme.
2024/07/07 Pprogression uses shorter range but enough internal states.
2024/07/08 merge latest lieonn, fix readme typo.
2024/09/07 add pp3.cc .
2024/09/09 merge some of the calculation result, p8 readme into lieonn predv0, predv also pp3.cc.
2024/09/10 compat with ddpmopt latest lieonn.hh.
2024/09/22 update readme. some of the fixes.
2024/09/22 append dft hack, releave.
2024/09/24 merge latest ddpmopt result, eliminate p1.cc.
2024/09/25 elim dead code. update readme.
2024/09/26 update lieonn so some rewrite is needed.
2024/09/27 update lieonn so some rewrite is needed.
2024/09/28 add step option.
2024/09/29 fix readme.
2024/11/14 fix step \> 2 case, rename output base pp3n to p1, the name is from old implementation reason.
2024/12/05 backport ddpmopt code brushup. exchanged argv[1] and argv[2] meaning.
2024/12/08 new p1 0 0 command line option is default now.
2024/12/13 really leave, close readme.md.
2024/12/14 shoud last update readme.md.
2024/12/26 merge latest ddpmopt result, no logic change.
2025/01/16 loop local variable name change, no binary meaning change with clang16 but might have change on another compilers.
2025/01/27 merge latest lieonn.
2025/02/07 add _CHAIN_ compile option.
2025/02/07 absent and integrate lastup into p2/persistent.cc.
2025/02/27 elim step parameter on pp3.cc .
2025/03/09 merge latest lieonn.
2025/03/17 revert step param.
2025/04/17 merge latest dimension auto tuner from ddpmopt. fixed step argv works well.
2025/04/18 eliminate step parameter, they doesn't improve results.
2025/04/19 merge latest lieonn.
2025/05/23 merge latest ddpmopt result also 'p1 d' argv1 can causes ddpmopt deep prediction result.
2025/05/25 merge latest lieonn, code cleaning, use deep inspection.
2025/06/08 merge latest lieonn.
2025/06/11 compat compile option to gcc4.2.1.
2025/06/12 compat compile option with one variant of gcc2.95.3.
2025/06/25 readme.md moved into implatnt lieonn.hh comment.
2025/06/28 refactor and fix around lieonn, re-compat with gcc2953.
2025/06/29-30 merge latest ddpmopt result.
2025/07/01 merge latest ddpmopt result.
2025/07/02-03 merge latest ddpmopt result, no logic change.
2025/07/04 merge latest ddpmopt result, no logic change.
2025/07/06 merge latest lieonn.
2025/07/13 merge latest lieonn.
2025/07/14-16 merge latest lieonn.
2025/07/17-19 merge latest lieonn.
2025/07/20 merge latest lieonn.
2025/07/24 merge latest lieonn.
2025/07/25 merge latest lieonn.
2025/07/26-28 merge latest lieonn.
2025/08/01 merge latest lieonn.
2025/08/01 re-enable step option.
2025/08/02-03 merge latest lieonn.
2025/08/04-06 merge latest lieonn.
2025/08/11 merge latest lieonn.
2025/08/12-16 merge latest lieonn.
2025/08/17-23 merge latest lieonn.
2025/08/25 merge latest lieonn.
2025/09/01 merge latest lieonn.

