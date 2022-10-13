#ifndef ERROREXCEPTION_HPP
# define ERROREXCEPTION_HPP

# include <exception>
# include <string>

class ErrorException : public std::exception {
    private:
      int m_statusCode;
      std::string m_error_file;

    public:
      ErrorException(int statusCode, std::string errorFile = "./app/error_pages/template.html")
      : m_statusCode(statusCode), m_error_file(errorFile) {}

	  ~ErrorException() throw() {};
      
      int getCode() const throw() {
        return (m_statusCode);
      }

      std::string getFile() const throw() {
        return (m_error_file);
      }
};

#endif
