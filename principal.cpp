#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    // Lista de productos
    m_productos.append(new Producto(1,"Leche",0.85));
    m_productos.append(new Producto(2,"Pan",0.15));
    m_productos.append(new Producto(3,"Queso",2.00));
    // Mostrar la lista de productos en combo
    for(int i=0;i<m_productos.size();++i)
    {
        ui->inProducto->addItem(m_productos.at(i)->nombre());
    }
    // Colocar cabecera de la tabla
    QStringList cabecera = {"Cantidad", "Producto", "Subtotal"};
    ui->outDetalle->setColumnCount(3);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    // Inicializar subtotal global
    m_subtotal = 0;
}

Principal::~Principal()
{
    delete ui;
}

void Principal::on_cmdAgregar_released()
{
    // Validar que no se agreguen productos con 0 cantidad
    int cantidad = ui->inCantidad->value();
    if(cantidad == 0)
        return;
    // Obtener datos de la GUI
    int index = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(index);


    // Calcular el subtotal del producto
    float subtotal = cantidad * p->precio();

    // Agregar datos a la tabla
    int fila = ui->outDetalle->rowCount();
    ui->outDetalle->insertRow(fila);
    ui->outDetalle->setItem(fila,0,new QTableWidgetItem(QString::number(cantidad)));
    ui->outDetalle->setItem(fila,1,new QTableWidgetItem(p->nombre()));
    ui->outDetalle->setItem(fila,2,new QTableWidgetItem(QString::number(subtotal,'f',2)));

    //Agregar datos
    informacion = informacion + "\nCant: " + QString::number(cantidad) +
            "\nProducto: " + p->nombre() +
            "\nSubTotal Producto: $" + QString::number(subtotal,'f',2) + "\n";

    // Limpiar datos
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();

    // Invocar a calcular
    calcular(subtotal);
}

void Principal::on_inProducto_currentIndexChanged(int index)
{
    // Obtener el precio del producto
    float precio = m_productos.at(index)->precio();
    // Mostrar el precio
    ui->outPrecio->setText("$ " + QString::number(precio,'f',2));
}

void Principal::calcular(float stProducto)
{
    m_subtotal += stProducto;
    m_iva = m_subtotal * IVA / 100;
    m_total = m_subtotal + m_iva;

    ui->outSubtotal->setText(QString::number(m_subtotal,'f',2));
    ui->outIva->setText(QString::number(m_iva,'f',2));
    ui->outTotal->setText(QString::number(m_total,'f',2));
}

void Principal::validarCedula()
{
    QString cedula = ui->inCedula->text();
    if (cedula.length() != 10){
        ui->inCedula->setStyleSheet("background-color: rgb(239, 41, 41);");
    }else{
        ui->inCedula->setStyleSheet("background-color: rgb(132, 225, 113);");
    }
}

bool Principal::verificarCedulaEcuatoriana(QString cedula)
{
    QString temp[10];
    int aux;
    int sumaPar = 0;
    int sumaImpar = 0;

    for(int i = 0; i < 9; i++)
    {
        temp[i] = cedula[i];
        aux = temp[i].toInt();
        if((i+1)%2==0)
            sumaPar += aux;
        else
        {
            if(aux * 2 > 9)
                sumaImpar = sumaImpar + ((aux * 2) - 9);
            else
                sumaImpar += aux * 2;
        }
    }
    int ultimoCedula = cedula.toInt()%10;
    int verificador = (sumaPar + sumaImpar)%10;
    if(verificador !=0)
        verificador = 10 - verificador;
    return ultimoCedula == verificador? true : false;
}

void Principal::borrar()
{
    ui->inCedula->setText("");
    ui->inNombre->setText("");;
    ui->inTelefono->setText("");;
    ui->inEmail->setText("");;
    ui->inDireccion->setText("");;
    ui->inCedula->setFocus();
    informacion.clear();
    ui->outDetalle->setRowCount(0);
    m_subtotal = 0;
    ui->outSubtotal->setText("$ " + QString::number(m_subtotal, 'f', 2));
    ui->outIva->setText("$ " + QString::number(0.0, 'f', 2));
    ui->outTotal->setText("$ " + QString::number(0.0, 'f', 2));
}

void Principal::validarNombre()
{
    QString nombre = ui->inNombre->text();
    if (nombre.isEmpty()){
        ui->inNombre->setStyleSheet("background-color: rgb(239, 41, 41);");
    }else{
        ui->inNombre->setStyleSheet("background-color: rgb(132, 225, 113);");
    }
}

void Principal::on_cmdFinalizar_released()
{
    QString cedula = ui->inCedula->text();
    QString nombre = ui->inNombre->text();
    QString telf = ui->inTelefono->text();
    QString correo = ui->inEmail->text();
    QString dir = ui->inDireccion->toPlainText();

    if(informacion.isEmpty())
    {
        QMessageBox::warning(this,"Tienda","No hay productos seleccionados");
        return;
    }
    else if(cedula == "9999999999")
    {
        Cliente *clien = new Cliente();
        Factura *compra= new Factura();
        compra->setCliente(clien->informacion());
        compra->setResumenProductos(informacion);
        compra->setSubtotal("Subtotal Compra: $ " + QString::number(m_subtotal, 'f', 2));
        compra->setIva("Iva Compra: $ " + QString::number(m_iva, 'f', 2));
        compra->setTotal("Total Compra: $ " + QString::number(m_total, 'f', 2));
        compra->show();
        borrar();
    }
    else if(nombre.isEmpty())
    {
        QMessageBox::warning(this,"Tienda","No has proporcionado el nombre o esta incorrecto");
        return;
    }
    else if(verificarCedulaEcuatoriana(cedula))
    {
        Cliente *clien = new Cliente(cedula, nombre, telf, correo, dir);
        Factura *compra = new Factura();
        compra->setCliente(clien->informacion());
        compra->setResumenProductos(informacion);
        compra->setSubtotal("Subtotal Compra: $ " + QString::number(m_subtotal, 'f', 2));
        compra->setIva("Iva Compra: $ " + QString::number(m_iva, 'f', 2));
        compra->setTotal("Total Compra: $ " + QString::number(m_total, 'f', 2));
        compra->show();
        borrar();
    }
    else if(!verificarCedulaEcuatoriana(cedula))
    {
        QMessageBox::warning(this,"Tienda","La cedula no pertenece a ninguna región del país");
        return;
    }
}

void Principal::on_inCedula_editingFinished()
{
    validarCedula();
}

void Principal::on_inNombre_editingFinished()
{
    validarNombre();
}
