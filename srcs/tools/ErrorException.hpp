#ifndef ERROREXCEPTION_HPP
# define ERROREXCEPTION_HPP

# include <exception>
# include <string>

class ErrorException : public std::exception {
    private:
      int m_statusCode;

    public:
      ErrorException(int statusCode) : m_statusCode(statusCode) {}
      int getCode() const throw() {
        return (m_statusCode);
      }
};

#endif
