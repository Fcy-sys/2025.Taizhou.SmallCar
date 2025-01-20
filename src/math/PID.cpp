#include "_includes.h"

PID::PID():firstTime(true), arrived(false), IMax(20), IRange(50), jumpTime(100) {
}

void PID::setTarget(float _target) {target = _target;}                  //����Ŀ��ֵ
void PID::setIMax(float _IMax) {IMax = _IMax;}                          //���û������ޣ���ֹ���ֱ���
void PID::setOutputmax(float _Outputmax){Outputmax = _Outputmax;}       //�������ֵ����
void PID::setIRange(float _IRange) {IRange = _IRange;}                  //���û��ֿ�ʼ��Χ                
void PID::setErrorTolerance(float _errorTol) {errorTol = _errorTol;}    //����������̶ȣ��ﵽ������Ϊ����Ŀ��,ֵԽС���ԽС
void PID::setDTolerance(float _DTol){DTol = _DTol;}                     //����΢�����̶ȣ�DС�ڴ�ֵ����Ϊ����Ŀ�ֵ꣬ԽСֹͣʱ���ٶ�ԽС
void PID::setJumpTime(float _jumpTime) {jumpTime = _jumpTime;}          //ûɶ��
bool PID::targetArrived() {return arrived;}                             //�����Ƿ񵽴�Ŀ��
void PID::setCoefficient(float _kp, float _ki, float _kd) {kp = _kp; ki = _ki; kd = _kd;}  //����PID����

void PID::refresh() {                       //��ʼ��
    firstTime = true;
    arrived = false;
}

void PID::update(float input) {             //λ��ʽPID�ĸ��¼���
    errorCurt = target - input;
    P = kp * errorCurt;
    if (firstTime) {
        firstTime = false;
        errorLast = errorCurt;
        errorInt = 0;
    }
    errorDev = errorCurt - errorLast;
    errorLast = errorCurt;
    D = kd * errorDev;
    if (fabs(P) >= IRange) {
        errorInt = 0;
    } else {
        errorInt += errorCurt;
        if (fabs(errorInt) * ki > IMax)
            errorInt = sign(errorInt) * IMax / ki;
    }
    if (sign(errorInt) != sign(errorCurt) || fabs(errorCurt) <= errorTol) errorInt = 0;
    I = ki * errorInt;
    if (fabs(errorCurt) <= errorTol && fabs(D) <= DTol) {
        arrived = true;
    } else {
        arrived = false;
    }
    output = P + I + D;
    int direction = sign(output);
    output = fmin(fabs(output), fabs(Outputmax)) * direction;
}

float PID::getOutput() {return output;}         //�������ֵ

/// @brief λ��ʽPID������õ�������������̾���ֵ
/// @param pid��������ַ��&pidRot�� 
/// @param ����ֵ
/// @param ��ǰֵ
/// @return ���ֵ
double PID::PID_Absolute(PID *pidRot, float target_val, float now_val)
{
    pidRot->target = target_val;
    pidRot->update(now_val);
    return pidRot->output;
}

/// @brief pid��������ʼ��
/// @param &pidRot, kp, ki, kd, ����޷�, ���ֿ�ʼ��Χ, ��������, ������̶�, ΢�����̶� 
void PID::init(PID *pidRot, float kp, float ki, float kd, float limit_value, float IRange, float IMax, float ErrorTol, float DTol)
{
    pidRot->setCoefficient(kp, ki, kd);
    pidRot->errorPrev = pidRot->errorLast = pidRot->errorCurt = pidRot->output = 0;
    pidRot->setOutputmax(limit_value);
    pidRot->setIRange(IRange);
    pidRot->setIMax(IMax);
    pidRot->setErrorTolerance(ErrorTol);
    pidRot->setDTolerance(DTol);
    pidRot->refresh();
}

/// @brief ����ʽpid������õ���������
/// @param pid�������ĵ�ַ��&pidRot�� 
/// @param ����ֵ
/// @param ��ǰʵ��ֵ 
/// @return ����
double PID::PID_Incremental(PID *pidRot, float target_val, float now_val)   
{
    pidRot->errorCurt = target_val - now_val;
    pidRot->P = pidRot->kp * (pidRot->errorCurt - pidRot->errorLast);

    pidRot->errorDev = pidRot->errorCurt + pidRot->errorPrev - 2 * pidRot->errorLast;
    pidRot->D = pidRot->kd * pidRot->errorDev;

    pidRot->I = pidRot->ki * pidRot->errorCurt;
    
    pidRot->errorPrev = pidRot->errorLast;
    pidRot->errorLast = pidRot->errorCurt;
    
    pidRot->output = -pidRot->P + pidRot->I - pidRot->D;
    int direction = sign(pidRot->output);
    pidRot->output = fmin(fabs(pidRot->output), fabs(pidRot->Outputmax)) * direction;
    return pidRot->output;
}
