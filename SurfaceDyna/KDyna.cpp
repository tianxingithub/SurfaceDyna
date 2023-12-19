#include "KDyna.h"

KDyna::KDyna(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::KDynaClass())
{
	ui->setupUi(this);
	ui->tabWidget->clear();

	m_keditor = new KFileEdtitor;



	QWidget* tab1 = new QWidget;
	QWidget* tab2 = new QWidget;

	QVBoxLayout* layout1 = new QVBoxLayout(tab1);
	QVBoxLayout* layout2 = new QVBoxLayout(tab2);

	//layout1->addWidget(m_keditor);
	layout2->addWidget(m_keditor);
	ui->tabWidget->addTab(tab1, u8"首页");
	ui->tabWidget->addTab(tab2, u8"开始");


	stateSlot();
	// 连接 currentChanged 信号到槽函数
	QObject::connect(ui->tabWidget, &QTabWidget::currentChanged, this,&KDyna::tabChangedSlot);
}

KDyna::~KDyna()
{
	delete ui;
}

void KDyna::stateSlot()
{
	//ui->tabWidget->setTabEnabled(1, m_btnState);
}

void KDyna::tabChangedSlot()
{
	auto index = ui->tabWidget->currentIndex();
	if (index == 0)
	{
		m_btnState = !m_btnState;
	}

	stateSlot();
}
