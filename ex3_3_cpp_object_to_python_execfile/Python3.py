def predict_on_data(o):
    print ("In Python:", flush=True)
    print (repr(o))
    # print the data members in o
    print ("o.slope is " + repr(o.slope))
    print ("o.compliance is " + repr(o.compliance))
    print ("o.Torso_LV is " + repr(o.Torso_LV))
    print ("o.m_DsOsAVs is " + repr(o.DsOsAVs))
    # modify some data
    o.slope = -1.0
    o.compliance = -2.0
