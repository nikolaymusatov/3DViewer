#include "model.h"
#include <iostream>

using namespace s21;

void Model::parseFile(QString& path)
{
    indices.clear();
    vertices.clear();
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

void Model::process(QString& path)
{
    parseFile(path);
    centerModel();
}

// QVector<QVector3D>* Model::changeScale(GLfloat ratio)
// {
//     static QVector<QVector3D> tmp;
//     tmp.clear();
//     for (size_t i = 0; i < vertices.size(); i++)
//         tmp.append(QVector3D(vertices[i].x() * ratio,
//                              vertices[i].y() * ratio,
//                              vertices[i].z() * ratio));
//     return &tmp;
// }

// QVector<QVector3D> *Model::moveModel(GLfloat x, GLfloat y, GLfloat z)
// {
//     static QVector<QVector3D> tmp;
//     tmp.clear();
//     for (size_t i = 0; i < vertices.size(); i++)
//         tmp.append(QVector3D(vertices[i].x() + x,
//                              vertices[i].y() * y,
//                              vertices[i].z() * z));
//     return &tmp;
// }

QVector<QVector3D> *Model::getVertices()
{
    return &vertices;
}

QVector<GLuint> *Model::getIndices()
{
    return &indices;
}

void Model::parseVertice(QStringList &line)
{
    vertices.append(QVector3D(line[1].toFloat(), line[2].toFloat(), line[3].toFloat()));
}

void Model::parseFace(QStringList &line)
{
    GLuint first;
    for (int i = 1; i < line.size(); i++) {
        QStringList point = line[i].split("/", Qt::SkipEmptyParts);
        if (i == 1) {
            first = point[0].toLong() - 1;
            indices.append(point[0].toLong() - 1);
        }
        indices.append(point[0].toLong() - 1);
        indices.append(point[0].toLong() - 1);
        if (i == line.size() - 1) indices.append(first);
    }
}

void Model::centerModel()
{
    QVector<QVector3D> tmp;
    QVector<GLfloat> ranges = {vertices[0].x(), vertices[0].x(),
                               vertices[0].y(), vertices[0].y(),
                               vertices[0].z(), vertices[0].z()};
    for (size_t i = 0; i < vertices.size(); i++) {
        if (vertices[i].x() < ranges[0]) ranges[0] = vertices[i].x();
        if (vertices[i].x() > ranges[1]) ranges[1] = vertices[i].x();
        if (vertices[i].x() < ranges[2]) ranges[2] = vertices[i].x();
        if (vertices[i].x() > ranges[3]) ranges[3] = vertices[i].x();
        if (vertices[i].x() < ranges[4]) ranges[4] = vertices[i].x();
        if (vertices[i].x() > ranges[5]) ranges[5] = vertices[i].x();
    }
    float xOffset = (ranges[0] + ranges[1]) * 0.5,
          yOffset = (ranges[2] + ranges[3]) * 0.5,
          zOffset = (ranges[4] + ranges[5]) * 0.5;
    float aspect = 2 / std::max({fabs(ranges[1] - ranges[0]),
                                 fabs(ranges[3] - ranges[2]),
                                 fabs(ranges[5] - ranges[4])});

    for (size_t i = 0; i < vertices.size(); i++)
        tmp.append(QVector3D((vertices[i].x() - xOffset) * aspect,
                             (vertices[i].y() - yOffset) * aspect,
                             (vertices[i].z() - zOffset) * aspect));
    vertices = tmp;
}


