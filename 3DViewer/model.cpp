#include "model.h"

using namespace s21;

void Model::parseFile(QString& path)
{
    object.clear();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) throw "Cant open file!";
    QTextStream input(&file);
    while (!input.atEnd()) {
        QString line = file.readLine().trimmed();
        QStringList lineParts = line.split(" ", Qt::SkipEmptyParts);
        if(lineParts.count() == 0) continue;
        if(lineParts[0] == "v") {
            parseVertice(lineParts);
        } else if(lineParts[0] == "f") {
            parseFace(lineParts);
        }
    }
    file.close();
}

Object *Model::getObject()
{
    return &object;
}

void Model::parseVertice(QStringList &line)
{
    for (int i = 1; i <=3; i++)
        object.addVertice(line[i].toFloat());
}

void Model::parseFace(QStringList &line)
{
    for (int i = 1; i < line.size(); i++) {
        QStringList point = line[i].split("/", Qt::SkipEmptyParts);
        object.addIndex(point[0].toLong() - 1);
    }
}


