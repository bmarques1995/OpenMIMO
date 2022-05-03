#ifndef DYNAMIC_SYSTEM_EXCEPTIONS_HPP
#define DYNAMIC_SYSTEM_EXCEPTIONS_HPP

#include <exception>
#include <sstream>

class DynamicSystemException : public std::exception
{
public:
    virtual const char * GetInfo() const = 0;
};

class BadTypeStartException : public DynamicSystemException
{
public:
    BadTypeStartException()
    {

    }

    virtual const char * GetInfo() const override
    {
        std::stringstream exceptionMessage;
        exceptionMessage << "The only input types allowed are float and double, another will be denied";
        m_Message = exceptionMessage.str();
        return m_Message.c_str();
    }
private:
    mutable std::string m_Message;
};

class BadNumeratorException : public DynamicSystemException
{
public:
    BadNumeratorException(size_t numeratorDegree, size_t denominatorDegree) :
        m_NumeratorDegree(numeratorDegree), m_DenominatorDegree(denominatorDegree)
    {

    }

    virtual const char * GetInfo() const override
    {
        std::stringstream exceptionMessage;
        exceptionMessage << "was expected that the numerator degree was, at most " << m_DenominatorDegree << ", but its degree is " << m_NumeratorDegree << ".";
        m_Message = exceptionMessage.str();
        return m_Message.c_str();
    }

private:
    size_t m_NumeratorDegree;
    size_t m_DenominatorDegree;
    mutable std::string m_Message;
};

class BadDynamicMatrixException : public DynamicSystemException
{
public:
    BadDynamicMatrixException(size_t stateMatrixRows, size_t stateMatrixCols) :
        m_StateMatrixRows(stateMatrixRows), m_StateMatrixCols(stateMatrixCols)
    {

    }

    virtual const char * GetInfo() const override
    {
        std::stringstream exceptionMessage;
        exceptionMessage << "was expected that the dynamic matrix was square but its dimensions is " << m_StateMatrixRows << "x" << m_StateMatrixCols << ".";
        m_Message = exceptionMessage.str();
        return m_Message.c_str();
    }

private:
    size_t m_StateMatrixRows;
    size_t m_StateMatrixCols;
    mutable std::string m_Message;
};

class BadInputMatrixException : public DynamicSystemException
{
public:
    BadInputMatrixException(size_t stateMatrixRows, size_t inputMatrixRows) :
        m_DynamicMatrixRows(stateMatrixRows), m_InputMatrixRows(inputMatrixRows)
    {

    }

    virtual const char * GetInfo() const override
    {
        std::stringstream exceptionMessage;
        exceptionMessage << "was expected that the input matrix had " << m_DynamicMatrixRows << " rows, but it has " << m_InputMatrixRows << ".";
        m_Message = exceptionMessage.str();
        return m_Message.c_str();
    }

private:
    size_t m_DynamicMatrixRows;
    size_t m_InputMatrixRows;
    mutable std::string m_Message;
};

class BadOutputMatrixException : public DynamicSystemException
{
public:
    BadOutputMatrixException(size_t stateMatrixCols, size_t outputMatrixCols) :
        m_DynamicMatrixCols(stateMatrixCols), m_OutputMatrixCols(outputMatrixCols)
    {

    }

    virtual const char * GetInfo() const override
    {
        std::stringstream exceptionMessage;
        exceptionMessage << "was expected that the output matrix had " << m_DynamicMatrixCols << " columns, but it has " << m_OutputMatrixCols << ".";
        m_Message = exceptionMessage.str();
        return m_Message.c_str();
    }

private:
    size_t m_DynamicMatrixCols;
    size_t m_OutputMatrixCols;
    mutable std::string m_Message;
};

class BadFeedForwardMatrixException : public DynamicSystemException
{
public:
    BadFeedForwardMatrixException(size_t outputMatrixRows, size_t inputMatrixCols, size_t directTransferMatrixRows, size_t directTransferMatrixCols) :
        m_OutputMatrixRows(outputMatrixRows), m_InputMatrixCols(inputMatrixCols),
        m_FeedForwardMatrixRows(directTransferMatrixRows), m_FeedForwardMatrixCols(directTransferMatrixCols)
    {

    }

    virtual const char * GetInfo() const override
    {
        std::stringstream exceptionMessage;
        exceptionMessage << "was expected that the direct transfer matrix had dimensions " << m_OutputMatrixRows << "x" << m_InputMatrixCols
        << ", but it has the following dimensions " << m_FeedForwardMatrixRows << "x" << m_FeedForwardMatrixCols << ".";
        m_Message = exceptionMessage.str();
        return m_Message.c_str();
    }

private:
    size_t m_OutputMatrixRows;
    size_t m_InputMatrixCols;
    size_t m_FeedForwardMatrixRows;
    size_t m_FeedForwardMatrixCols;
    mutable std::string m_Message;
};

#endif