#include "log_sys.hpp"

p_logger* p_logger::m_s_instance = nullptr;
std::shared_ptr<spdlog::logger> p_logger::m_log_ = nullptr;

p_logger::p_logger() {
  m_log_.reset();
  m_log_ = spdlog::basic_logger_mt("daydream", "p.log");
  m_s_instance = this;
}

p_logger::p_logger(const std::string& file_path) : m_file_path(file_path) {
  m_log_.reset();
  m_log_ = spdlog::basic_logger_mt("daydream", file_path);
  m_s_instance = this;
}

p_logger* p_logger::get_instance() { return m_s_instance; }

void p_logger::info(const std::string& rhs) {
  m_log_->info(rhs);
  m_log_->flush();
}

void p_logger::debug(const std::string& rhs) { m_log_->debug(rhs); }

void p_logger::error(const std::string& rhs) {
  m_log_->error(rhs);
  m_log_->flush();
}

void p_logger::warn(const std::string& rhs) {
  m_log_->warn(rhs);
  m_log_->flush();
}
