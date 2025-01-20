#ifndef KALMANFILTER_H
#define KALMANFILTER_H
#include <iostream>
#include <vector>
#include "Matrix.h"

class KalmanFilter {//�������˲���
protected:
    Matrix K;// ����������
public:
    Matrix F;// ״̬ת�ƾ��� 
    Matrix H;// �۲����
    Matrix Q;// ��������Э�������
    Matrix R;// ��������Э�������
    Matrix B;// �����������
    Matrix u;// ��������
    Matrix x;// ״̬����
    Matrix P;// Э�������

    KalmanFilter(const Matrix& a, const Matrix& b, const Matrix& c, const Matrix& d , const Matrix& e): 
    F(a), H(b), Q(c), R(d),B(e) {}

    void initialize(const std::vector<double>& x0, const Matrix& P0);

    /// @brief ����Ԥ��
    void predict(double u);
    void predict(const Matrix &u);

    /// @brief ������ֵ������һ������
    /// @param z �����������ֱ��ʹ�� vector ����
    void update(const std::vector<double>& z);
    void update(const Matrix &z);

    /// @brief ��ȡԤ��״̬
    std::vector<double> getState() const;
};
#endif