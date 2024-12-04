#include "registerdialog.h"
#include "ui_registerdialog.h"

#include <QDebug>
#include <QRegularExpression>
#include <QJsonDocument>
#include "global.h"
#include "httpmgr.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->lineEdit_Passwd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_Confirm->setEchoMode(QLineEdit::Password);

    ui->err_tip->setProperty("state", "normal");
    repolish(ui->err_tip);

    initHttpHandlers();

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::showTip(QString str, bool b_ok)
{
    if (b_ok) {
        ui->err_tip->setProperty("state", "normal");
    } else {
        ui->err_tip->setProperty("state", "err");
    }
    ui->err_tip->setText(str);
    repolish(ui->err_tip);
}

void RegisterDialog::on_get_code_clicked()
{
    qDebug() << "receive varify btn clicked";
    auto email = ui->email_edit->text();
    // 邮箱地址的正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if (match) {
        QJsonObject json_obj;
        json_obj["email"] = email;
        HttpMgr::GetInstance()->PostHttpReq(QUrl("/get_varifycode"), json_obj, ReqId::ID_GET_VARIFY_CODE, Modules::RESETMOD);
    } else {
        showTip(tr("邮箱地址不对"), false);
    }
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if (err != ErrorCodes::SUCCESS) {
        showTip(tr("网络请求错误"), false);
        return;
    }
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if (jsonDoc.isNull()) {
        showTip(tr("json解析错误"),false);
        return;
    }

    if (!jsonDoc.isObject()) {
        showTip(tr("json解析错误"),false);
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();
    _handlers[id](jsonObj);
}

void RegisterDialog::initHttpHandlers()
{
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if (error != ErrorCodes::SUCCESS) {
            showTip(tr("参数错误"), false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已发送到邮箱 注意查收"), true);
        qDebug() << "email is " << email;
    });
}

