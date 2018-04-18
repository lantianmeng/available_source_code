// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: activation.proto

#ifndef PROTOBUF_activation_2eproto__INCLUDED
#define PROTOBUF_activation_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_activation_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsNullRespImpl();
void InitDefaultsNullResp();
void InitDefaultsActivationReqImpl();
void InitDefaultsActivationReq();
inline void InitDefaults() {
  InitDefaultsNullResp();
  InitDefaultsActivationReq();
}
}  // namespace protobuf_activation_2eproto
namespace service {
class ActivationReq;
class ActivationReqDefaultTypeInternal;
extern ActivationReqDefaultTypeInternal _ActivationReq_default_instance_;
class NullResp;
class NullRespDefaultTypeInternal;
extern NullRespDefaultTypeInternal _NullResp_default_instance_;
}  // namespace service
namespace service {

// ===================================================================

class NullResp : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:service.NullResp) */ {
 public:
  NullResp();
  virtual ~NullResp();

  NullResp(const NullResp& from);

  inline NullResp& operator=(const NullResp& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  NullResp(NullResp&& from) noexcept
    : NullResp() {
    *this = ::std::move(from);
  }

  inline NullResp& operator=(NullResp&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const NullResp& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const NullResp* internal_default_instance() {
    return reinterpret_cast<const NullResp*>(
               &_NullResp_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(NullResp* other);
  friend void swap(NullResp& a, NullResp& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline NullResp* New() const PROTOBUF_FINAL { return New(NULL); }

  NullResp* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const NullResp& from);
  void MergeFrom(const NullResp& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(NullResp* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:service.NullResp)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  mutable int _cached_size_;
  friend struct ::protobuf_activation_2eproto::TableStruct;
  friend void ::protobuf_activation_2eproto::InitDefaultsNullRespImpl();
};
// -------------------------------------------------------------------

class ActivationReq : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:service.ActivationReq) */ {
 public:
  ActivationReq();
  virtual ~ActivationReq();

  ActivationReq(const ActivationReq& from);

  inline ActivationReq& operator=(const ActivationReq& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ActivationReq(ActivationReq&& from) noexcept
    : ActivationReq() {
    *this = ::std::move(from);
  }

  inline ActivationReq& operator=(ActivationReq&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const ActivationReq& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ActivationReq* internal_default_instance() {
    return reinterpret_cast<const ActivationReq*>(
               &_ActivationReq_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(ActivationReq* other);
  friend void swap(ActivationReq& a, ActivationReq& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ActivationReq* New() const PROTOBUF_FINAL { return New(NULL); }

  ActivationReq* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ActivationReq& from);
  void MergeFrom(const ActivationReq& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(ActivationReq* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string symbol = 1;
  void clear_symbol();
  static const int kSymbolFieldNumber = 1;
  const ::std::string& symbol() const;
  void set_symbol(const ::std::string& value);
  #if LANG_CXX11
  void set_symbol(::std::string&& value);
  #endif
  void set_symbol(const char* value);
  void set_symbol(const char* value, size_t size);
  ::std::string* mutable_symbol();
  ::std::string* release_symbol();
  void set_allocated_symbol(::std::string* symbol);

  // int32 activation = 2;
  void clear_activation();
  static const int kActivationFieldNumber = 2;
  ::google::protobuf::int32 activation() const;
  void set_activation(::google::protobuf::int32 value);

  // int32 cmd = 3;
  void clear_cmd();
  static const int kCmdFieldNumber = 3;
  ::google::protobuf::int32 cmd() const;
  void set_cmd(::google::protobuf::int32 value);

  // int32 mt4_id = 4;
  void clear_mt4_id();
  static const int kMt4IdFieldNumber = 4;
  ::google::protobuf::int32 mt4_id() const;
  void set_mt4_id(::google::protobuf::int32 value);

  // int32 volume = 5;
  void clear_volume();
  static const int kVolumeFieldNumber = 5;
  ::google::protobuf::int32 volume() const;
  void set_volume(::google::protobuf::int32 value);

  // int64 open_time = 7;
  void clear_open_time();
  static const int kOpenTimeFieldNumber = 7;
  ::google::protobuf::int64 open_time() const;
  void set_open_time(::google::protobuf::int64 value);

  // int64 close_time = 8;
  void clear_close_time();
  static const int kCloseTimeFieldNumber = 8;
  ::google::protobuf::int64 close_time() const;
  void set_close_time(::google::protobuf::int64 value);

  // double open_price = 9;
  void clear_open_price();
  static const int kOpenPriceFieldNumber = 9;
  double open_price() const;
  void set_open_price(double value);

  // double close_price = 10;
  void clear_close_price();
  static const int kClosePriceFieldNumber = 10;
  double close_price() const;
  void set_close_price(double value);

  // double profit = 11;
  void clear_profit();
  static const int kProfitFieldNumber = 11;
  double profit() const;
  void set_profit(double value);

  // double sl = 12;
  void clear_sl();
  static const int kSlFieldNumber = 12;
  double sl() const;
  void set_sl(double value);

  // double tp = 13;
  void clear_tp();
  static const int kTpFieldNumber = 13;
  double tp() const;
  void set_tp(double value);

  // int64 expiration = 14;
  void clear_expiration();
  static const int kExpirationFieldNumber = 14;
  ::google::protobuf::int64 expiration() const;
  void set_expiration(::google::protobuf::int64 value);

  // int64 time_stamp = 15;
  void clear_time_stamp();
  static const int kTimeStampFieldNumber = 15;
  ::google::protobuf::int64 time_stamp() const;
  void set_time_stamp(::google::protobuf::int64 value);

  // int32 ticket = 6;
  void clear_ticket();
  static const int kTicketFieldNumber = 6;
  ::google::protobuf::int32 ticket() const;
  void set_ticket(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:service.ActivationReq)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr symbol_;
  ::google::protobuf::int32 activation_;
  ::google::protobuf::int32 cmd_;
  ::google::protobuf::int32 mt4_id_;
  ::google::protobuf::int32 volume_;
  ::google::protobuf::int64 open_time_;
  ::google::protobuf::int64 close_time_;
  double open_price_;
  double close_price_;
  double profit_;
  double sl_;
  double tp_;
  ::google::protobuf::int64 expiration_;
  ::google::protobuf::int64 time_stamp_;
  ::google::protobuf::int32 ticket_;
  mutable int _cached_size_;
  friend struct ::protobuf_activation_2eproto::TableStruct;
  friend void ::protobuf_activation_2eproto::InitDefaultsActivationReqImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// NullResp

// -------------------------------------------------------------------

// ActivationReq

// string symbol = 1;
inline void ActivationReq::clear_symbol() {
  symbol_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ActivationReq::symbol() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.symbol)
  return symbol_.GetNoArena();
}
inline void ActivationReq::set_symbol(const ::std::string& value) {
  
  symbol_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:service.ActivationReq.symbol)
}
#if LANG_CXX11
inline void ActivationReq::set_symbol(::std::string&& value) {
  
  symbol_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:service.ActivationReq.symbol)
}
#endif
inline void ActivationReq::set_symbol(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  symbol_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:service.ActivationReq.symbol)
}
inline void ActivationReq::set_symbol(const char* value, size_t size) {
  
  symbol_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:service.ActivationReq.symbol)
}
inline ::std::string* ActivationReq::mutable_symbol() {
  
  // @@protoc_insertion_point(field_mutable:service.ActivationReq.symbol)
  return symbol_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ActivationReq::release_symbol() {
  // @@protoc_insertion_point(field_release:service.ActivationReq.symbol)
  
  return symbol_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ActivationReq::set_allocated_symbol(::std::string* symbol) {
  if (symbol != NULL) {
    
  } else {
    
  }
  symbol_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), symbol);
  // @@protoc_insertion_point(field_set_allocated:service.ActivationReq.symbol)
}

// int32 activation = 2;
inline void ActivationReq::clear_activation() {
  activation_ = 0;
}
inline ::google::protobuf::int32 ActivationReq::activation() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.activation)
  return activation_;
}
inline void ActivationReq::set_activation(::google::protobuf::int32 value) {
  
  activation_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.activation)
}

// int32 cmd = 3;
inline void ActivationReq::clear_cmd() {
  cmd_ = 0;
}
inline ::google::protobuf::int32 ActivationReq::cmd() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.cmd)
  return cmd_;
}
inline void ActivationReq::set_cmd(::google::protobuf::int32 value) {
  
  cmd_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.cmd)
}

// int32 mt4_id = 4;
inline void ActivationReq::clear_mt4_id() {
  mt4_id_ = 0;
}
inline ::google::protobuf::int32 ActivationReq::mt4_id() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.mt4_id)
  return mt4_id_;
}
inline void ActivationReq::set_mt4_id(::google::protobuf::int32 value) {
  
  mt4_id_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.mt4_id)
}

// int32 volume = 5;
inline void ActivationReq::clear_volume() {
  volume_ = 0;
}
inline ::google::protobuf::int32 ActivationReq::volume() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.volume)
  return volume_;
}
inline void ActivationReq::set_volume(::google::protobuf::int32 value) {
  
  volume_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.volume)
}

// int32 ticket = 6;
inline void ActivationReq::clear_ticket() {
  ticket_ = 0;
}
inline ::google::protobuf::int32 ActivationReq::ticket() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.ticket)
  return ticket_;
}
inline void ActivationReq::set_ticket(::google::protobuf::int32 value) {
  
  ticket_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.ticket)
}

// int64 open_time = 7;
inline void ActivationReq::clear_open_time() {
  open_time_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 ActivationReq::open_time() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.open_time)
  return open_time_;
}
inline void ActivationReq::set_open_time(::google::protobuf::int64 value) {
  
  open_time_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.open_time)
}

// int64 close_time = 8;
inline void ActivationReq::clear_close_time() {
  close_time_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 ActivationReq::close_time() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.close_time)
  return close_time_;
}
inline void ActivationReq::set_close_time(::google::protobuf::int64 value) {
  
  close_time_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.close_time)
}

// double open_price = 9;
inline void ActivationReq::clear_open_price() {
  open_price_ = 0;
}
inline double ActivationReq::open_price() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.open_price)
  return open_price_;
}
inline void ActivationReq::set_open_price(double value) {
  
  open_price_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.open_price)
}

// double close_price = 10;
inline void ActivationReq::clear_close_price() {
  close_price_ = 0;
}
inline double ActivationReq::close_price() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.close_price)
  return close_price_;
}
inline void ActivationReq::set_close_price(double value) {
  
  close_price_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.close_price)
}

// double profit = 11;
inline void ActivationReq::clear_profit() {
  profit_ = 0;
}
inline double ActivationReq::profit() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.profit)
  return profit_;
}
inline void ActivationReq::set_profit(double value) {
  
  profit_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.profit)
}

// double sl = 12;
inline void ActivationReq::clear_sl() {
  sl_ = 0;
}
inline double ActivationReq::sl() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.sl)
  return sl_;
}
inline void ActivationReq::set_sl(double value) {
  
  sl_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.sl)
}

// double tp = 13;
inline void ActivationReq::clear_tp() {
  tp_ = 0;
}
inline double ActivationReq::tp() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.tp)
  return tp_;
}
inline void ActivationReq::set_tp(double value) {
  
  tp_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.tp)
}

// int64 expiration = 14;
inline void ActivationReq::clear_expiration() {
  expiration_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 ActivationReq::expiration() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.expiration)
  return expiration_;
}
inline void ActivationReq::set_expiration(::google::protobuf::int64 value) {
  
  expiration_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.expiration)
}

// int64 time_stamp = 15;
inline void ActivationReq::clear_time_stamp() {
  time_stamp_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 ActivationReq::time_stamp() const {
  // @@protoc_insertion_point(field_get:service.ActivationReq.time_stamp)
  return time_stamp_;
}
inline void ActivationReq::set_time_stamp(::google::protobuf::int64 value) {
  
  time_stamp_ = value;
  // @@protoc_insertion_point(field_set:service.ActivationReq.time_stamp)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace service

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_activation_2eproto__INCLUDED
