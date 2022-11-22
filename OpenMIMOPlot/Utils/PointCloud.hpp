#ifndef POINT_CLOUD_HPP
#define POINT_CLOUD_HPP

#include <vector>

namespace OpenMIMO
{
    template<typename T>
    class PointCloud
    {
    public:
        PointCloud();
        
        void Start(size_t rows, size_t cols);
        void PushRow(const std::vector<T>& row);
        const std::vector<T>& GetColumn(size_t index);

        size_t GetNumberOfRows();
        size_t GetNumberOfCols();
    private:
        std::vector<std::vector<T>> m_PointCloud;
        size_t m_Rows;
        size_t m_Cols;
        bool m_Blocked = false;
    };

    
}

template<typename T>
inline OpenMIMO::PointCloud<T>::PointCloud()
{
    m_Rows = 0;
    m_Cols = 0;
}

template<typename T>
inline void OpenMIMO::PointCloud<T>::Start(size_t rows, size_t cols)
{
    if (!m_Blocked)
    {
        m_PointCloud.resize(rows*cols);
        m_Blocked = true;
        m_Rows = rows;
        m_Cols = cols;
    }
}

template<typename T>
inline void OpenMIMO::PointCloud<T>::PushRow(const std::vector<T>& row)
{
    if (row.size() != m_PointCloud.size())
        return;
    else
        for (size_t i = 0; i < row.size(); i++)
        {
            m_PointCloud[i].push_back(row[i]);
        }
}

template<typename T>
inline const std::vector<T>& OpenMIMO::PointCloud<T>::GetColumn(size_t index)
{
    if (index >= m_PointCloud.size())
        return std::vector<T>();
    else
        return m_PointCloud[index];
}

template<typename T>
inline size_t OpenMIMO::PointCloud<T>::GetNumberOfRows()
{
    return m_Rows;
}

template<typename T>
inline size_t OpenMIMO::PointCloud<T>::GetNumberOfCols()
{
    return m_Cols;
}


#endif // POINT_CLOUD_HPP
