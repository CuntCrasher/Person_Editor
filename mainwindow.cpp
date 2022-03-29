#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_intValidator (0, 10,this)//задаём допустимые значения
{
    ui->setupUi(this);


    ui->lineEdit_Str->setValidator(&m_intValidator);//включаем валидатор в "силе"
    ui->lineEdit_Dex->setValidator(&m_intValidator);//включаем валидатор в "ловкости"
    ui->lineEdit_Int->setValidator(&m_intValidator);//включаем валидатор в "интелекте"
    ui->lineEdit_Luck->setValidator(&m_intValidator);//включаем вылидатор в "удаче"

    connect(ui->lineEdit_Str, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));//падаём сигнал к валидатору при изменению вводимых данных
    connect(ui->lineEdit_Dex, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
    connect(ui->lineEdit_Int, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
    connect(ui->lineEdit_Luck, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));

    ui->pushButton_Clear->click();

    ui->lineEdit_Name->setMaxLength(20); //максимальная длина строки
    ui->lineEdit_Str->setMaxLength(2); //максимальная длина силы
    ui->lineEdit_Dex->setMaxLength(2); //макс ловкость
    ui->lineEdit_Int->setMaxLength(2); //макс интел
    ui->lineEdit_Luck->setMaxLength(2); //макс удача

    ui->lineEdit_Score_Left->setReadOnly(true);

    //инициализация массивов
    //сила
    mas_str[0][0]=1; //люди мин
    mas_str[0][1]=10; //люди макс
    mas_str[1][0]=1; //эльфы мин
    mas_str[1][1]=8;//эльфы макс
    mas_str[2][0]=3; //орки мин
    mas_str[2][1]=10; //орки макс
    mas_str[3][0]=3; //гномы мин
    mas_str[3][1]=9; //гномы макс
    //ловкость
    mas_dex[0][0]=1; //люди мин
    mas_dex[0][1]=7; //люди макс
    mas_dex[1][0]=3; //эльфы мин
    mas_dex[1][1]=10; //эльфы макс
    mas_dex[2][0]=1; //орки мин
    mas_dex[2][1]=5; //орки макс
    mas_dex[3][0]=1; //гномы мин
    mas_dex[3][1]=6; //гномы макс
    //интеллект
    mas_intel[0][0]=2; //люди мин
    mas_intel[0][1]=10; //люди макс
    mas_intel[1][0]=4; //эльфы мин
    mas_intel[1][1]=10;//эльфы макс
    mas_intel[2][0]=1; //орки мин
    mas_intel[2][1]=8; //орки макс
    mas_intel[3][0]=1; //гномы мин
    mas_intel[3][1]=9; //гномы макс
    //удача
    mas_luck[0][0]=2; //люди мин
    mas_luck[0][1]=8; //люди макс
    mas_luck[1][0]=1; //эльфы мин
    mas_luck[1][1]=9;//эльфы макс
    mas_luck[2][0]=1; //орки мин
    mas_luck[2][1]=6; //орки макс
    mas_luck[3][0]=3; //гномы мин
    mas_luck[3][1]=10; //гномы макс
    //остальное сами дома ;-)
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_Clear_clicked() //очистка лайнэдитов в начале
{
    ui->lineEdit_Name->clear();
    ui->lineEdit_Str->clear();
    ui->lineEdit_Dex->clear();
    ui->lineEdit_Int->clear();
    ui->lineEdit_Luck->clear();

    ui->label_HP_Value->clear();
    ui->label_MP_Value->clear();
    ui->label_Atk_Value->clear();
    ui->label_Def_Value->clear();
    ui->label_Class_Value->clear();

    ui->radioButton_Sex_M->setChecked(true);

    ui->lineEdit_Score_Left->setText("20");
}

void MainWindow::on_pushButton_Create_clicked() //прописываем нажатие кнопки "создать"
{
    QString name; //имя
    int dlina; //длина имени
    bool flag; //признак успешности генерации
    int str,dex,intel,luck; //параметры
    int index_race; //индекс расы

    index_race=ui->comboBox_Race->currentIndex(); //раса


    name=ui->lineEdit_Name->text();
    dlina=name.length(); //определили длину имени
    if ((dlina<3)||(dlina > 20))
    {
        flag=false;
        QMessageBox::information(this,"Ошибка","Имя должно быть от 3 до 20 символов.",QMessageBox::Ok);
    }
    else
        flag=true;

    //Сила
    str=0;
    if (flag) //Вместо вложенных условий
    {
        str=ui->lineEdit_Str->text().toInt(&flag);
        if (flag)
        {
            if ((str<mas_str[index_race][0])||(str>mas_str[index_race][1]))
            {
                flag=false;
                QMessageBox::information(this,"Ошибка","\"Сила\" должна быть от "+
                                         QString::number(mas_str[index_race][0])+" до "+
                        QString::number(mas_str[index_race][1])+"." ,QMessageBox::Ok);
            }
        }
        else
            QMessageBox::information(this,"Ошибка","Неправильное значение параметра \"Сила\".",QMessageBox::Ok);


    }

    //Тут самим доделать ввод и проверку Ловкости, Интеллекта и Удачи

    //Ловкость
    dex=0;
    if (flag) //Вместо вложенных условий
    {
        dex=ui->lineEdit_Dex->text().toInt(&flag);
        if (flag)
        {
            if ((dex<mas_dex[index_race][0])||(dex>mas_dex[index_race][1]))
            {
                flag=false;
                QMessageBox::information(this,"Ошибка","\"Ловкость\" должна быть от "+
                                         QString::number(mas_dex[index_race][0])+" до "+
                        QString::number(mas_dex[index_race][1])+"." ,QMessageBox::Ok);
            }
        }
        else
            QMessageBox::information(this,"Ошибка","Неправильное значение параметра \"Ловкость\".",QMessageBox::Ok);
    }

    //Интеллект
    intel=0;
    if (flag) //Вместо вложенных условий
    {
        intel=ui->lineEdit_Int->text().toInt(&flag);
        if (flag)
        {
            if ((intel<mas_intel[index_race][0])||(intel>mas_intel[index_race][1]))
            {
                flag=false;
                QMessageBox::information(this,"Ошибка","\"Интеллект\" должен быть от "+
                                         QString::number(mas_intel[index_race][0])+" до "+
                        QString::number(mas_intel[index_race][1])+"." ,QMessageBox::Ok);
            }
        }
        else
            QMessageBox::information(this,"Ошибка","Неправильное значение параметра \"Интеллект\".",QMessageBox::Ok);
    }

    //Удача
    luck=0;
    if (flag) //Вместо вложенных условий
    {
        luck=ui->lineEdit_Luck->text().toInt(&flag);
        if (flag)
        {
            if ((luck<mas_luck[index_race][0])||(luck>mas_luck[index_race][1]))
            {
                flag=false;
                QMessageBox::information(this,"Ошибка","\"Удача\" должна быть от "+
                                         QString::number(mas_luck[index_race][0])+" до "+
                        QString::number(mas_luck[index_race][1])+"." ,QMessageBox::Ok);
            }
        }
        else
            QMessageBox::information(this,"Ошибка","Неправильное значение параметра \"Удача\".",QMessageBox::Ok);
    }

    //проверка количества очков
    if (flag)
    {
        int score_left=20-str-dex-intel-luck;
        ui->lineEdit_Score_Left->setText(QString::number(score_left));
        if (score_left!=0)
        {
            flag=false;
            if (score_left<0)
                QMessageBox::information(this,"Ошибка","Нельзя тратить больше 20 очков.",QMessageBox::Ok);
            else
                QMessageBox::information(this,"Ошибка","Нужно потратить все очки.",QMessageBox::Ok);
        }
    }

    //расчет параметров и вывод результата
    if (flag)
    {
        int hp,mp,atk,def;
        hp=8*str+2*dex;
        mp=8*intel+dex+luck;
        atk=6*str+2*dex+2*luck;
        def=7*dex+3*luck;

        ui->label_HP_Value->setNum(hp);
        ui->label_MP_Value->setNum(mp);
        ui->label_Atk_Value->setNum(atk);
        ui->label_Def_Value->setNum(def);

        //класс самостоятельно с учетом пола

        //классы

        QString mas_classes[4][4][2]=
        {
            {//раса людей
             {"Офицер","Офицерша"},//танк
             {"Ниндзя","Ниндзя"},//ловкие
             {"Учёный","Учёная"},//хиллеры
             {"Победитель в лотерею","Победительница в лотерею"},//маги
            },
            {//раса эльфов
             {"Офицер","Офицерша"},//танк
             {"Ниндзя","Ниндзя"},//ловкие
             {"Учёный","Учёная"},//хиллеры
             {"Победитель в лотерею","Победительница в лотерею"},//маги
            },
            {//раса орки
             {"Офицер","Офицерша"},//танк
             {"Ниндзя","Ниндзя"},//ловкие
             {"Учёный","Учёная"},//хиллеры
             {"Победитель в лотерею","Победительница в лотерею"},//маги
            },
            {//раса гномов
             {"Офицер","Офицерша"},//танк
             {"Ниндзя","Ниндзя"},//ловкие
             {"Учёный","Учёная"},//хиллеры
             {"Победитель в лотерею","Победительница в лотерею"},//маги
            }
        };//задали массив с классами.[4]-кол-во рас,[4]-кол-во классов,[2]-кол-во полов
        //ищем максимальное значение из всех четырёх параметров
        int max = -1;

        if (str>max)
            max=str;

        if (dex>max)
            max=dex;

        if (intel>max)
            max=intel;

        if (luck>max)
            max=luck;

        //флаги для определения являются те или иные параметры максимальными

        bool max_str=false;
        bool max_dex=false;
        bool max_intel=false;
        bool max_luck=false;

        int maxes_count = 0;

        if (str == max)//если значение силы совпадает с максимальным, то ставим true
        {
            max_str=true;
            maxes_count++;
        }
        if (dex == max)//если значение ловкости совпадает с максимальным, то ставим true
        {
            max_dex=true;
            maxes_count++;
        }
        if (intel == max)//если значение интелекта совпадает с максимальным, то ставим true
        {
            max_intel=true;
            maxes_count++;
        }
        if (luck == max)//если значение удачи совпадает с максимальным, то ставим true
        {
            max_luck=true;
            maxes_count++;
        }

        if (maxes_count>1)
        {
            if(index_race == 0)//для людей
            {
                //принудительная установка
                max_str = false;
                max_dex = false;
                max_intel = true;
                max_luck = false;
            }
            else
                if(index_race == 1)//для эльфов
                {
                    //принудительная установка
                    max_str = false;
                    max_dex = true;
                    max_intel = false;
                    max_luck = false;
                }
                else
                    if (index_race == 2)//для орков
                    {
                        //принудительная установка
                        max_str = true;
                        max_dex = false;
                        max_intel = false;
                        max_luck = false;
                    }
                    else
                        if(index_race == 3)//для гномов
                        {
                            //принудительная установка
                            max_str = false;
                            max_dex = false;
                            max_intel = false;
                            max_luck = true;
                        }
        }

        // присваиваем значение класса в зависимости от максимального параметра
        int class_index = -1;

        if (max_str)
            class_index = 0;
        else
            if (max_dex)
                class_index = 1;
            else
                if (max_intel)
                    class_index =2;
                else
                    if (max_luck)
                        class_index = 3;

        //присваиваем значение пола в зависимости от выбранного
        int pol = -1;
        if(ui->radioButton_Sex_M->isChecked())
            pol = 0;
        else
            if (ui->radioButton_Sex_W->isChecked())
                pol = 1;
        if ((str==intel) and (intel==dex) and (dex==luck))
            ui->label_Class_Value->setText("Дмитрий Анатольевич");
                    else
            {
                QString class_name = mas_classes[index_race][class_index][pol];
                ui->label_Class_Value->setText(class_name);//выводим класс
            }
    }

    else
    {//при неверных значениях очищаем результаты
        ui->label_HP_Value->clear();
        ui->label_MP_Value->clear();
        ui->label_Atk_Value->clear();
        ui->label_Def_Value->clear();
        ui->label_Class_Value->clear();
    }
}

void MainWindow::on_lineEdit_Name_textChanged(const QString &) //изменили имя
{
    int dlina=ui->lineEdit_Name->text().length(); //узнали длину

    QPalette pal=ui->lineEdit_Name->palette(); //вызываем палитру
    if ((dlina<3))
        pal.setColor(QPalette::Text,Qt::red); //красный
    else
        pal.setColor(QPalette::Text,Qt::green); //зеленый

    ui->lineEdit_Name->setPalette(pal);
}

void MainWindow::on_lineEdit_Str_textChanged(const QString &) //изменили силу
{
    int val=ui->lineEdit_Str->text().toInt(); //узнали длину
    int index_race=ui->comboBox_Race->currentIndex();

    QPalette pal=ui->lineEdit_Str->palette(); //вызываем палитру
    if ((val<mas_str[index_race][0])||(val>mas_str[index_race][1]))
        pal.setColor(QPalette::Text,Qt::red); //красный
    else
        pal.setColor(QPalette::Text,Qt::green); //зеленый

    ui->lineEdit_Str->setPalette(pal);

    calc_score();
    score_str();
}

void MainWindow::on_lineEdit_Dex_textChanged(const QString &) //ловкость
{
    int val=ui->lineEdit_Dex->text().toInt(); //узнали длину
    int index_race=ui->comboBox_Race->currentIndex();

    QPalette pal=ui->lineEdit_Dex->palette(); //вызываем палитру
    if ((val<mas_dex[index_race][0])||(val>mas_dex[index_race][1]))
        pal.setColor(QPalette::Text,Qt::red); //красный
    else
        pal.setColor(QPalette::Text,Qt::green); //зеленый

    ui->lineEdit_Dex->setPalette(pal);

    calc_score();
    score_dex();
}

void MainWindow::on_lineEdit_Int_textChanged(const QString &) //интеллект
{
    int val=ui->lineEdit_Int->text().toInt(); //узнали длину
    int index_race=ui->comboBox_Race->currentIndex();

    QPalette pal=ui->lineEdit_Int->palette(); //вызываем палитру
    if ((val<mas_intel[index_race][0])||(val>mas_intel[index_race][1]))
        pal.setColor(QPalette::Text,Qt::red); //красный
    else
        pal.setColor(QPalette::Text,Qt::green); //зеленый

    ui->lineEdit_Int->setPalette(pal);

    calc_score();
    score_int();
}

void MainWindow::on_lineEdit_Luck_textChanged(const QString &) //удача
{
    int val=ui->lineEdit_Luck->text().toInt(); //узнали длину
    int index_race=ui->comboBox_Race->currentIndex();

    QPalette pal=ui->lineEdit_Luck->palette(); //вызываем палитру
    if ((val<mas_luck[index_race][0])||(val>mas_luck[index_race][1]))
        pal.setColor(QPalette::Text,Qt::red); //красный
    else
        pal.setColor(QPalette::Text,Qt::green); //зеленый

    ui->lineEdit_Luck->setPalette(pal);

    calc_score();
    score_luck();
}

void MainWindow::calc_score() //расчет и проверка очков
{
    int str, dex, intel, luck, score_left; //заводим переменные

    str=ui->lineEdit_Str->text().toInt();
    dex=ui->lineEdit_Dex->text().toInt();
    intel=ui->lineEdit_Int->text().toInt();
    luck=ui->lineEdit_Luck->text().toInt();

    score_left=20-str-dex-intel-luck;

    QPalette pal=ui->lineEdit_Score_Left->palette(); //вызываем палитру
    QColor col;
    col.setRgb(250,238,221);
    if ((score_left<=20)&&(score_left>=10))
        pal.setColor(QPalette::Text,Qt::red); //красный
    //        pal.setColor(QPalette::Text,col);
    else if ((score_left<9)&&(score_left>0))
        pal.setColor(QPalette::Text,Qt::yellow); //зеленый
    else if ((score_left)<0)
        pal.setColor(QPalette::Text,Qt::red);
    else pal.setColor(QPalette::Text,Qt::green);

    ui->lineEdit_Score_Left->setPalette(pal);
    ui->lineEdit_Score_Left->setText(QString::number(score_left));
}

void MainWindow:: score_str() //меняем цвет букв Силы
{
    int str,str_left;
    int index_race=ui->comboBox_Race->currentIndex();

    str=ui->lineEdit_Str->text().toInt(); //задаем значение силы

    str_left=str;

    QPalette pal=ui->label__Str->palette(); //заводим палитру
    QColor col;
    col.setRgb(255,165,0);
    if ((str_left<=0)||(str_left>mas_str[index_race][1])||(str_left<mas_str[index_race][0]))
        pal.setColor(QPalette::WindowText,Qt::black); //черный
    else if ((str_left<4)&&(str_left>0))
        pal.setColor(QPalette::WindowText,Qt::red); //красный
    else if ((str_left>=4)&&(str_left<=7))
        pal.setColor(QPalette::WindowText,col);
    else if ((str_left>=8)&&(str_left<=10))
        pal.setColor(QPalette::WindowText,Qt::green); //зеленый
    else
        pal.setColor(QPalette::WindowText,Qt::black);

    ui->label__Str->setPalette(pal);
}

void MainWindow:: score_dex() //меняем цвет букв Ловкости
{
    int dex,dex_left;
    int index_race=ui->comboBox_Race->currentIndex();

    dex=ui->lineEdit_Dex->text().toInt(); //задаем переменную

    dex_left=dex;

    QPalette pal=ui->label_Dex->palette(); //создаем палитру
    QColor col;
    col.setRgb(255,165,0);

    if (((dex_left)<=0)||(dex_left>mas_dex[index_race][1])||(dex_left<mas_dex[index_race][0]))
        pal.setColor(QPalette::WindowText,Qt::black); //черный
    else if ((dex_left<4)&&(dex_left>0))
        pal.setColor(QPalette::WindowText,Qt::red);
    else
        if ((dex_left>=4)&&(dex_left<=7))
            pal.setColor(QPalette::WindowText,col);
        else
            if ((dex_left>=8)&&(dex_left<=10))
                pal.setColor(QPalette::WindowText,Qt::green);
            else
                pal.setColor(QPalette::WindowText,Qt::black);

    ui->label_Dex->setPalette(pal);
}

void MainWindow:: score_int() //меняем цвет букв Интеллекта
{
    int intel,intel_left;
    int index_race=ui->comboBox_Race->currentIndex();

    intel=ui->lineEdit_Int->text().toInt();

    intel_left=intel;

    QPalette pal=ui->label_Int->palette();
    QColor col;
    col.setRgb(255,165,0);

    if (((intel_left)<=0)||(intel_left>mas_intel[index_race][1])||(intel_left<mas_intel[index_race][0]))
        pal.setColor(QPalette::WindowText,Qt::black);
    else if ((intel_left<4)&&(intel_left>0))
        pal.setColor(QPalette::WindowText,Qt::red);
    else
        if ((intel_left>=4)&&(intel_left<=7))
            pal.setColor(QPalette::WindowText,col);
        else
            if ((intel_left>=8)&&(intel_left<=10))
                pal.setColor(QPalette::WindowText,Qt::green);
            else
                pal.setColor(QPalette::WindowText,Qt::black);

    ui->label_Int->setPalette(pal);
}

void MainWindow:: score_luck() //меняем цвет букв Удачи
{
    int luck,luck_left;
    int index_race=ui->comboBox_Race->currentIndex();

    luck=ui->lineEdit_Luck->text().toInt();

    luck_left=luck;

    QPalette pal=ui->label_Luck->palette();
    QColor col;
    col.setRgb(255,165,0);

    if (((luck_left)<=0)||(luck_left>mas_luck[index_race][1])||(luck_left<mas_luck[index_race][0]))
        pal.setColor(QPalette::WindowText,Qt::black);
    else if ((luck_left<4)&&(luck_left>0))
        pal.setColor(QPalette::WindowText,Qt::red);
    else
        if ((luck_left>=4)&&(luck_left<=7))
            pal.setColor(QPalette::WindowText,col);
        else
            if ((luck_left>=8)&&(luck_left<=10))
                pal.setColor(QPalette::WindowText,Qt::green);
            else
                pal.setColor(QPalette::WindowText,Qt::black);

    ui->label_Luck->setPalette(pal);
}


void MainWindow::on_comboBox_Race_currentIndexChanged(int) //изменили расы
{
    on_lineEdit_Str_textChanged(""); //сила
    on_lineEdit_Dex_textChanged(""); //ловкость
    on_lineEdit_Int_textChanged(""); //интеллект
    on_lineEdit_Luck_textChanged(""); //удача
}

