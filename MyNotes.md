```bash
source env.sh

./scripts/setup_rivet_plugins.sh

./scripts/setup_process.sh hemu_sq

# python scripts/make_config.py -p hemu_sq -o config_HEL_STXS.json --pars smeft:4,5,6,7,8,9,10,11,12 --def-val 0.01 --def-sm 0.0 --def-gen 0.0

python scripts/make_config.py -p hemu_sq -o config_HEL_STXS.json --pars smeft:4,5 --def-val 0.01 --def-sm 0.0 --def-gen 0.0


# [rasharma@lxplus743 EFT2Obs]$ python scripts/make_config.py -p hemu_sq -o config_HEL_STXS.json --pars smeft:4,5 --def-val 0.01 --def-sm 0.0 --def-gen 0.0
# >> Parsing MG5_aMC_v2_6_7/hemu_sq/Cards/param_card.dat to get the list of model parameters
# >> Selecting 2/60 parameters in block smeft:
#     - [4] chbox
#     - [5] chdd
# >> Writing config file config_HEL_STXS.json

python scripts/make_param_card.py -p hemu_sq -c config_HEL_STXS.json -o cards/hemu_sq/param_card.dat


python scripts/make_reweight_card.py config_HEL_STXS.json cards/hemu_sq/reweight_card.dat


./scripts/make_gridpack.sh hemu_sq


export HIGGSPRODMODE=ZH
python scripts/run_gridpack.py --gridpack gridpack_hemu_sq.tar.gz -s 1 -e 500 -p HiggsDecayParTemplate  -o hemu_sq --rivet-ignore-beams


yodamerge -o hemu_sq/Rivet.yoda hemu_sq/Rivet_*


python scripts/get_scaling.py -c config_HEL_STXS.json -i hemu_sq/Rivet.yoda --hist "/HiggsDecayParTemplate/pT_Higgs" --save json,txt,tex --translate-tex resources/translate_tex.json --rebin 0,10,20,30,40,50,60,70,80,90,100,120,140,160,180,200,250,300,350,400

# python scripts/makePlot.py --hist RamHiggsTemplate_pT_Higgs.json -c config_HEL_STXS.json --x-title "p_{T}(H) [GeV]" --title-left "qq #rightarrow Hl^{+}l^{-}" --title-right "SMEFT UFO" --ratio 0.9,1.95 --draw chw=0.005:4 cww=0.005:2 cb=0.005:8 ca=0.05:12 --show-unc --y-min 1E-9 --translate resources/translate_root.json

python scripts/makePlot.py --hist HiggsDecayParTemplate_pT_Higgs.json -c config_HEL_STXS.json --x-title "p_{T}(H) [GeV]" --title-left "qq #rightarrow Hl^{+}l^{-}" --title-right "SMEFT UFO" --ratio 0.9,1.95 --draw chbox=0.005:4 chdd=0.005:2 --show-unc --y-min 1E-9 --translate resources/translate_root.json

```
