RegisterCallBack(Update, BearObject, Update, float time, time);
RegisterCallBack(Destroy, BearObject, Destroy, , );
RegisterCallBack(Resize, BearObjectResize, Resize, BEAR_MAKE_WITH_COMMA(bsize width, bsize height), BEAR_MAKE_WITH_COMMA(width, height));
RegisterCallBack(AppActive, BearObjectAppActive, AppActive, , );
RegisterCallBack(AppDeactive, BearObjectAppDeactive, AppDeactive, , );