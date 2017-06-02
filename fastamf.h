#ifndef FASTAMF_H
#define FASTAMF_H
#include "filtr.h"

class FASTAMF : public Filtr
{
private:
    double ProgVal;
public:

    FASTAMF(void);
    FASTAMF(int);
    ~FASTAMF();
    void setProgVal(double_t);
    double_t getProgVal() const;
    virtual QImage filtr();
};

#endif // FASTAMF_H
