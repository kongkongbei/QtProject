#ifndef MEMBERINFO_H
#define MEMBERINFO_H
#include<QString>
#include<QDate>
#include<QLabel>

class MemberInfo
{
public:
    MemberInfo();
    ~MemberInfo();

    //不算重要的数据
    int m_Sex; //性别
    QString m_Origin; //籍贯
    QString m_Birthday; //出生日期
    QString m_Headshot; //头像
    int m_Politics; //政治面貌
    QString m_Address; //家庭住址
    QString m_Education; //教育经历
    QString m_Award; //获得奖项
    QString m_Specialty; //特长

    MemberInfo(const QString &mName, int mSex,
                QString mOrigin, QString mBir, QString mHead,
                int mPol, QString mAddress, QString mEdu,
               QString mAward, QString mSpec)
        :m_Sex(mSex),  m_Origin(mOrigin), m_Birthday(mBir),
        m_Headshot(mHead), m_Politics(mPol), m_Address(mAddress), m_Education(mEdu),
        m_Award(mAward), m_Specialty(mSpec){setName(mName);}

    //获取姓名信息-应该改为getName
    QString readName() const {return m_Name;}

    //设置姓名信息
    void setName(const QString &name) {m_Name = name;}

    //保存信息
    void saveInfo(MemberInfo member);


private:
    //需要被多次访问的数据
    QString m_Name;//姓名
};

#endif // MEMBERINFO_H
