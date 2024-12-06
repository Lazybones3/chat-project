#include "global.h"

QString gate_url_prefix = "";

std::function<void(QWidget*)> repolish = [](QWidget* w){
    // 抹去旧的样式
    w->style()->unpolish(w);
    // 涂上新的样式
    w->style()->polish(w);
};
