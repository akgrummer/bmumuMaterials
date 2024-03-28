import os
import shutil

#****************************************
def copy_files(user):
    main_file="split_main_%s" % d_datasets[user][0]
    dely_file="split_dely_%s" % d_datasets[user][1]

    main_source="datasets/%s" % main_file
    main_target="%s/%s" % (NEW_DATASETS_DIR, main_file)

    dely_source="datasets/%s" % dely_file
    dely_target="%s/%s" % (NEW_DATASETS_DIR, dely_file)

    print("copying %s ----> %s" % (main_source, main_target) )
    print("copying %s ----> %s" % (dely_source, dely_target) )

    shutil.copyfile(main_source, main_target)
    shutil.copyfile(dely_source, dely_target)
#****************************************
def make_updated(user, stream):
    tp_datasets = d_datasets[user]
    file_id = tp_datasets[0] if stream == "main" else tp_datasets[1]

    ifile=open("./datasets/split_%s_%s" % (stream, file_id) )
    l_dataset = ifile.read().splitlines()
    ifile.close()

    ofile=open("%s/split_%s_%s" % (NEW_DATASETS_DIR, stream, file_id), "w")

    for dataset in l_dataset:
        if dataset in d_exclude[user]:
            continue

        ofile.write("%s\n" % dataset)

    ofile.close()
#****************************************
def add_excluded(stream):
    tp_datasets = d_datasets["angel"]
    file_id = tp_datasets[0] if stream == "main" else tp_datasets[1]
    
    ifile = open("datasets/split_%s_%s" % (stream, file_id) )
    l_dataset = ifile.read().splitlines()
    ifile.close()

    for user in d_exclude:
        for dataset in d_exclude[user]:
            not_main = ("Main" in dataset) and (stream != "main")
            not_dely = ("Delayed" in dataset) and (stream != "dely")

            if not_main or not_dely:
                continue
            
            l_dataset.append(dataset)

    for dataset in to_angel:
        not_main = ("Main" in dataset) and (stream != "main")
        not_dely = ("Delayed" in dataset) and (stream != "dely")

        if not_main or not_dely:
            continue
            
        l_dataset.append(dataset)


    ofile = open("%s/split_%s_%s" % (NEW_DATASETS_DIR, stream, file_id), "w")
    for dataset in l_dataset:
        ofile.write("%s\n" % dataset)
    ofile.close()
#****************************************
NEW_DATASETS_DIR="updated_datasets"

if os.path.isdir(NEW_DATASETS_DIR):
    shutil.rmtree(NEW_DATASETS_DIR)

os.mkdir(NEW_DATASETS_DIR)
#****************************************
d_datasets=dict()

d_datasets["aidan"]   =("00", "00")
d_datasets["angel"]   =("06", "04")
d_datasets["iskander"]=("01", "01")
d_datasets["fabio"]   =("02", "02")
d_datasets["pavel"]   =("03", "03")
d_datasets["serguei"] =("04", "05")
d_datasets["umberto"] =("05", "06")
#****************************************
to_angel=list()
#Delayed stream with wrong reco tag
to_angel.append("data16_13TeV.00304128.physics_BphysDelayed.merge.DAOD_BPHY8.r8847_p2884_p3255_tid12276683_00")
#Main stream, exhausted
to_angel.append("data16_13TeV.00300571.physics_Main.merge.DAOD_BPHY8.f705_m1606_p3255_tid11999709_00")
to_angel.append("data16_13TeV.00303421.physics_Main.merge.DAOD_BPHY8.f716_m1620_p3255_tid11999859_00")
to_angel.append("data16_13TeV.00300908.physics_Main.merge.DAOD_BPHY8.f708_m1606_p3255_tid11999735_00")

no_umberto=list()
no_umberto.append("data15_13TeV.00280464.physics_Main.merge.DAOD_BPHY8.r7562_p2521_p3255_tid11998196_00")
no_umberto.append("data15_13TeV.00284484.physics_Main.merge.DAOD_BPHY8.r7562_p2521_p3255_tid11998403_00")

no_fabio=list()
no_fabio.append("data16_13TeV.00310249.physics_Main.merge.DAOD_BPHY8.f755_m1699_p3255_tid12000237_00")

no_pavel=list()
no_pavel.append("data16_13TeV.00303892.physics_Main.merge.DAOD_BPHY8.f716_m1620_p3255_tid11999894_00")

d_exclude=dict()
d_exclude["umberto"] = no_umberto
d_exclude["fabio"]   = no_fabio
d_exclude["pavel"]   = no_pavel
#****************************************
for user in d_datasets:
    if user not in d_exclude:
        print("Copying files for user %s" % user)
        copy_files(user)
        continue

    print("Excluding for user:%s" % user)

    make_updated(user, "main")
    make_updated(user, "dely")
#****************************************
add_excluded("main")
add_excluded("dely")

