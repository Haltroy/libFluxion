//
// Created by haltroy on 01.05.2024.
//

#ifndef FLUXIONEXCEPTION_H
#define FLUXIONEXCEPTION_H
#include <exception>
#include <string>
#include <utility>

class FluxionException : public std::exception
{
public:
  explicit FluxionException(std::string message) : message_(std::move(message))
  {
  }

  const char *what() const noexcept override
  {
    return message_.c_str();
  }

private:
  std::string message_;
};

class FluxionInvalidHeaderException final : public FluxionException
{
public:
  FluxionInvalidHeaderException() : FluxionException("Header does not contain valid FLX mark.")
  {
  }
};

class FluxionEndOfStreamException final : public FluxionException
{
public:
  FluxionEndOfStreamException() : FluxionException("End of the stream reached prematurely.")
  {
  }
};

class FluxionEncodingException final : public FluxionException
{
public:
  explicit FluxionEncodingException(const std::string &encoding) : FluxionException(
                                                                       "Encoding \"" + encoding + "\" is not implemented.")
  {
  }

  explicit FluxionEncodingException(const unsigned char id) : FluxionException(
                                                                  "Encoding with ID \"" + std::to_string(id) + "\" is not implemented.")
  {
  }
};

class FluxionValueTypeException final : public FluxionException
{
public:
  explicit FluxionValueTypeException(const unsigned char id) : FluxionException(
                                                                   "Value type with ID \"" + std::to_string(id) + "\" is not implemented.")
  {
  }
};

class FluxionParentException final : public FluxionException
{
public:
  explicit FluxionParentException() : FluxionException(
                                          "Cannot add node to self or into the same tree.")
  {
  }
};

class FluxionUnsupportedVersionException final : public FluxionException
{
public:
  explicit FluxionUnsupportedVersionException(unsigned char version) : FluxionException("Version \"" + std::to_string(version) + "\" is currently not supported by Fluxion. Please upgrade your libFluxion installation to a newer version.") {}
};

#endif // FLUXIONEXCEPTION_H
