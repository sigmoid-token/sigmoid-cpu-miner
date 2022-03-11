#ifndef _SOLVER_H_
#define _SOLVER_H_

#include <atomic>
#include <mutex>
#include <string>
#include <vector>

#include "balloon.h"

class Solver
{
public:
  typedef std::vector<uint8_t> bytes_t;

  static const unsigned short ADDRESS_LENGTH = 20u;
  static const unsigned short UINT256_LENGTH = 32u;

public:
  Solver() noexcept;

public:
  void setAddress(std::string const& addr);

  void setChallenge(std::string const& chal);

  void setTarget(std::string const& target);

  void setParameters(int s_cost, int t_cost, int delta);

  void setWhetherBalloon(bool is_balloon);

public:
  bool trySolution(bytes_t const& solution);

public:
  static void hexToBytes(std::string const& hex, bytes_t& bytes);

  static std::string bytesToString(bytes_t const& buffer);

  static bool lte(bytes_t const& left, bytes_t const& right);

private:
  void updateBuffer();

  void hash(bytes_t const& solution, bytes_t& digest);

private:
  bool is_balloon = true;
  int s_cost = 256;
  int t_cost = 3;
  int delta = 3;
  bytes_t m_address;
  bytes_t m_challenge;
  bytes_t m_target, m_target_tmp;
  bytes_t m_buffer, m_buffer_tmp;
  std::mutex m_buffer_mutex;
  std::mutex m_target_mutex;
  std::atomic<bool> m_buffer_ready;
  std::atomic<bool> m_target_ready;
  BalloonHasher balloon_hasher;

public:
  static std::atomic<uint32_t> hashes;
};

#endif // !_SOLVER_H_
