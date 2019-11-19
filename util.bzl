def if_has_hector_slam(a):
    return select({
        "//:has_hector_slam": a,
        "//conditions:default": [],
    })

def if_has_orb_slam2(a):
    return select({
        "//:has_orb_slam2": a,
        "//conditions:default": [],
    })
