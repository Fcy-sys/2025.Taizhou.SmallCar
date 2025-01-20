#include "_includes.h"

using namespace std;

/// @brief ��ʼ��
/// @param x0 ��ʼ״̬
/// @param P0 Э������󣬸о���������զ�ؾ������裬������С���ԽǾ���
void KalmanFilter::initialize(const vector<double>& x0, const Matrix& P0) {
    size_t state_size = x0.size();
    x = Matrix(state_size, 1);
    for (size_t i = 0; i < state_size; ++i) {
        x[i][0] = x0[i];
    }
    P = P0;
}

/// @brief ����Ԥ��
void KalmanFilter::predict(double u) {
    x = F*x+(B*u);
    P = F.multiply(P).multiply(F.transpose()).add(Q);
}
void KalmanFilter::predict(const Matrix &u) {
    x = F*x+(B*u);
    P = F.multiply(P).multiply(F.transpose()).add(Q);
}
/// @brief ������ֵ������һ������
/// @param z �����������ֱ��ʹ�� vector ����
void KalmanFilter::update(const vector<double>& z) {
    Matrix Z(z.size(), 1);
    for (size_t i = 0; i < z.size(); ++i) {
        Z[i][0] = z[i];
    }
    Matrix S = H*P*(H.transpose())+(R);
    Matrix K = P*(H.transpose())*(S.invert());
    Matrix y = Z-H*x;
    x = x+K*y;
    Matrix I = Matrix::identity(x.rows());
    P = (I-K*H)*P;
}
/// @brief ������ֵ������һ������
/// @param z �����������ֱ��ʹ�þ��󼴿�
void KalmanFilter::update(const Matrix& z) {
    Matrix S = H*P*(H.transpose())+(R);
    K = P*(H.transpose())*(S.invert());
    x = x+K*(z-H*x);
    Matrix I = Matrix::identity(x.rows());
    P = (I-K*H)*P;
}

/// @brief ��ȡԤ��״̬
std::vector<double> KalmanFilter::getState() const {
    std::vector<double> state(x.rows());
    for (size_t i = 0; i < x.rows(); ++i) {
        state[i] = x.mat[i][0];
    }
    return state;
}
