#pragma once

#include <QtWidgets/QWidget>
#include "ui_ShowResults.h"
#include <QTreeWidget>
#include <QTableWidget>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QMessageBox>

class ShowResults : public QWidget
{
    Q_OBJECT

public:
    ShowResults(QWidget *parent, std::vector<std::string>);
    ~ShowResults();
    //向结果中加入数据
    //void addDataToTable(QTableWidget* tableWidget, const QString& 姓名, const QString& 描述, const QString& 出生日期,
    //    const QString& 电话, const QString& 邮箱, const QString& QQ,
    //    const QString& 公司, const QString& 职位);
    //为了获取显示结果表格的指针
    QTableWidget* getTableWidget() const { return tableWidget; }


    //用于设置整体界面的样式和字体
    void applyStyles();
    void show();

public slots:
    void onItemClicked(QTreeWidgetItem* item, int column);

private:
    Ui::ShowResultsClass ui;

    //显示结果
    QTreeWidgetItem* rootItem = nullptr;
    QTreeWidgetItem* qqNumberItem = nullptr;
    QTreeWidgetItem* userInfoItem = nullptr;
    QTreeWidgetItem* contactsItem = nullptr;
    QTreeWidgetItem* messagesItem = nullptr;
    QTreeWidgetItem* photosItem = nullptr;
    QTreeWidgetItem* otherItem = nullptr;

    QHBoxLayout* mainLayout = nullptr;
    QWidget* mainWindow = nullptr;

    QTreeWidget* treeWidget = nullptr;
    QTableWidget* tableWidget = nullptr;
    QScrollArea* scrollArea = nullptr;

    int currentRowCount = 0;
};
