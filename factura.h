#ifndef FACTURA_H
#define FACTURA_H

#include <QDialog>
#include <QWidget>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class Factura;
}

class Factura : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QString dato READ dato WRITE setDato)

public:
    explicit Factura(QWidget *parent = nullptr);
    ~Factura();

    QString dato() const;
    void setDato(const QString &dato);

    void setCliente(QString cliente);
    void setResumenProductos(QString informacion);
    void setSubtotal(QString subtotal);
    void setIva(QString iva);
    void setTotal(QString total);

private slots:
    void on_pushButton_released();

private:
    Ui::Factura *ui;
    QString m_dato;
};

#endif // FACTURA_H
