#include "s11dataresearch.h"

S11DataResearch::S11DataResearch()
{

}

QString S11DataResearch::readFile(QString fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        return "Ошибка чтения файла!";
    }
    QTextStream in(&file);
    in.setCodec("Windows-1251");
    int dataCount = lineCount(fileName);
    std::vector<double> frequency(dataCount);
    std::vector<std::complex<double>> s11Complex(dataCount);
    int i = 0;
    if (isValid(in)) {
        QStringList dataItems;
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            dataItems = line.split(QRegExp("\\s+"));
            if (QVariant(dataItems[0]).canConvert<double>() &&
                    QVariant(dataItems[0]).canConvert<double>() &&
                    QVariant(dataItems[0]).canConvert<double>()) {
                frequency[i] = dataItems[0].toDouble();
                s11Complex[i] = std::complex<double>(dataItems[1].toDouble(), dataItems[2].toDouble());
            }
            else {
                return "Ошибка чтения данных!";
            }
            ++i;
        }
        frequency.resize(i-1);
        s11Complex.resize(i-1);
    }
    else {
        return "Неподходящий формат данных!";
    }
    std::vector<double> s11Value = complexCalculation(s11Complex);
    s11_xMin = frequency[0];
    s11_xMax = frequency[i-1];
    generateData(i-1, frequency, s11Value);
    return "Ok";
}

bool S11DataResearch::isValid(QTextStream &in)
{
    QString header = in.readLine();
    if (header[0] == '#' && header.mid(1).contains("Hz S RI R 50")) {
        header = in.readLine();
        if (header[0] == '!' && header.mid(1).contains("Date:")) {
            QStringList dateTime = header.split(QRegExp("\\s+"));
            s11_date = dateTime[2];
            s11_time = dateTime[3] + " " + dateTime[4];
            header = in.readLine();
            if (header[0] == '!' && header.mid(1).contains(QRegExp("Freq"))
                                 && header.mid(1).contains(QRegExp("\\s S11"))) {
                return true;
            }
        }
    }
    return false;
}

size_t S11DataResearch::lineCount(const QString fileName)
{
    QFile File(fileName);
    if (!File.open(QFile::ReadOnly)) return -1;

    char   buff[1024*128];
    size_t lcount = 0;
    int    len;

    char prev = 0;
    char cur  = 0;
    for(;;) {
        len = File.read(buff, sizeof(buff));
        if (File.error()) return -1;
        if(!len) {break;}

        for (int i=0; i<len; ++i) {
            cur = buff[i];
            if      (cur  == 10) {++lcount;}
            else if (prev == 13) {++lcount;}
            prev = cur;
        }
    }
    if (cur == 13) {++lcount;}
    return lcount + 1;
}

QVector<QPointF> S11DataResearch::getData() const
{
    return s11_data;
}

void S11DataResearch::getDateTime(QString &date, QString &time)
{
    date = s11_date;
    time = s11_time;
}

void S11DataResearch::getGraphGeometry(qreal &xMin, qreal &xMax, qreal &yMin, qreal &yMax)
{
    xMin = s11_xMin;
    xMax = s11_xMax;
    yMin = s11_yMin;
    yMax = s11_yMax;
}
//Расчет значения s11 из комплексного числа
std::vector<double> S11DataResearch::complexCalculation(const std::vector<std::complex<double> > vectorCmplx)
{
    s11_yMin = __DBL_MAX__;
    s11_yMax = (__DBL_MAX__)*(-1);
    unsigned int dataSize = vectorCmplx.size();
    std::vector<double> s11Res(dataSize);
    s11Res.resize(vectorCmplx.size());

    for (unsigned int i = 0; i < dataSize; ++i) {
        s11Res[i] = (20 * log10(std::abs(vectorCmplx[i])));
        if (s11_yMin>s11Res[i]) {s11_yMin = s11Res[i]; continue;}
        if (s11_yMax < s11Res[i]) s11_yMax = s11Res[i];
    }
    return s11Res;
}

void S11DataResearch::generateData(const int pointsCount, const std::vector<double> frequencyX,
                                   const std::vector<double> s11ResY)
{
    s11_data.clear();
    QVector<QPointF> points;
    points.reserve(pointsCount);

    for (int i = 0; i < pointsCount; ++i) {
        double x;
        double y;

        x = frequencyX[i];
        y = s11ResY[i];
        points.append(QPointF(x, y));
    }
    s11_data.append(points);
}
