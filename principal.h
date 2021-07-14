#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QMessageBox>
#include "producto.h"
#include "factura.h"
#include "cliente.h"

#define IVA 12

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

private slots:
    void on_cmdAgregar_released();
    void on_inProducto_currentIndexChanged(int index);
    void on_cmdFinalizar_released();

    void on_inCedula_editingFinished();

    void on_inNombre_editingFinished();

private:
    Ui::Principal *ui;
    QList<Producto*> m_productos;
    float m_subtotal;
    float m_iva;
    float m_total;
    void calcular(float stProducto);
    void validarCedula();
    bool verificarCedulaEcuatoriana(QString cedula);
    void borrar();
    void validarNombre();
    QString informacion;
};
#endif // PRINCIPAL_H
