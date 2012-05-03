#include "search/vocab.hh"

#include "lm/virtual_interface.hh"
#include "util/string_piece.hh"

namespace search {

Vocab::Vocab(const lm::base::Vocabulary &backing) : backing_(backing) {
  end_sentence_ = FindOrAdd("</s>");
}

Word Vocab::FindOrAdd(const StringPiece &str) {
  Map::const_iterator i(FindStringPiece(map_, str));
  if (i != map_.end()) return Word(*i);
  std::pair<std::string, lm::WordIndex> to_ins;
  to_ins.first.assign(str.data(), str.size());
  to_ins.second = backing_.Index(str);
  return Word(*map_.insert(to_ins).first);
}

} // namespace search