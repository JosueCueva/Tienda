#include "factura.h"
#include "ui_factura.h"

Factura::Factura(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Factura)
{
    ui->setupUi(this);
}

Factura::~Factura()
{
    delete ui;
}

QString Factura::dato() const
{
    return m_dato;
}

void Factura::setDato(const QString &dato)
{
    m_dato = dato;
}

void Factura::setCliente(QString cliente)
{
    ui->outCliente->setPlainText(cliente);
}

void Factura::setResumenProductos(QString informacion)
{
    ui->outResumen->setPlainText(informacion);
}

void Factura::setSubtotal(QString subtotal)
{
    ui->outSubtotal->setText(subtotal);
}

void Factura::setIva(QString iva)
{
    ui->outIva->setText(iva);
}

void Factura::setTotal(QString total)
{
    ui->outTotal->setText(total);
}

void Factura::on_pushButton_released()
{
    QDir directorio = QDir::home();
    QString pathArchivo = directorio.absolutePath() + "/Compra.txt";
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar archivo", pathArchivo, "Archivo de texto(*.txt)");
    QFile f(fileName);
    QTextStream out(&f);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QMessageBox::warning(this, "Factura", "No se pudo guardar el archivo");
        return;
    }
    out << "Factura:\n " << ui->outCliente->toPlainText() << "\nResumen de la compra:\n" << ui->outResumen->toPlainText() << "\n" << ui->outSubtotal->toPlainText() << "\n" << ui->outIva->toPlainText() << "\n" << ui->outTotal->toPlainText();
    f.close();
    this->hide();
}
