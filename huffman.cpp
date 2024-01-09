#include "huffman.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>

struct Node {
	Node() = default;
	Node(uint8_t val) : term(true), val(val) {
	}
	std::shared_ptr<Node> DeepCopy() {
		Node copy = *this;
		for (int i : {0, 1}) {
			if (nxt[i]) {
				copy.nxt[i] = copy.nxt[i]->DeepCopy();
			}
		}
		return std::make_shared<Node>(copy);
	}
	bool term;
	uint8_t val;
	std::shared_ptr<Node> nxt[2];
};

class HuffmanTree::Impl {
public:
	Impl() = default;
	void Build(std::vector<uint8_t> code_lengths, const std::vector<uint8_t> &values) {
		if (code_lengths.size() > 16) {
			throw std::invalid_argument("Size of code lenghts cannot exceed 16");
		}
		root_ = std::shared_ptr<Node>(new Node());
		root_->nxt[0] = std::shared_ptr<Node>(new Node());
		root_->nxt[1] = std::shared_ptr<Node>(new Node());
		size_t term_count = 0;
		DepthFirstSearch(root_->nxt[0], 0, term_count, code_lengths, values);
		DepthFirstSearch(root_->nxt[1], 0, term_count, code_lengths, values);
		if (term_count != values.size()) {
			throw std::invalid_argument("Values array is incorrect: could not use all value");
		}
		for (const auto &num : code_lengths) {
			if (num != 0) {
				throw std::invalid_argument(
						"Code lenghts array is incorrect: could not build huffman tree");
			}
		}
		node_ = root_;
	}

	bool Move(bool bit, int &value) {
		if (root_ == nullptr) {
			throw std::invalid_argument("Huffman tree was not build =(");
		}
		if (!node_->nxt[bit]) {
			throw std::invalid_argument("Cannot move in huffman tree.");
		}
		node_ = node_->nxt[bit];
		if (node_->term) {
			value = node_->val;
			node_ = root_;
			return true;
		}
		return false;
	}

private:
	std::shared_ptr<Node> root_;
	std::shared_ptr<Node> node_;
	void DepthFirstSearch(std::shared_ptr<Node> cur, uint8_t height, size_t &term_count,
						  std::vector<uint8_t> &code_lengths, const std::vector<uint8_t> &values) {
		if (height >= code_lengths.size()) {
			return;
		}
		if (code_lengths[height] > 0) {
			if (term_count >= values.size()) {
				throw std::invalid_argument("Not enough values in array");
			}
			cur->val = values[term_count++];
			cur->term = true;
			code_lengths[height]--;
			return;
		}
		bool need = false;

		for (int i : {0, 1}) {
			cur->nxt[i] = std::shared_ptr<Node>(new Node());
			for (size_t h = height + 1; h < code_lengths.size(); ++h) {
				if (code_lengths[h] > 0) {
					need = true;
					break;
				}
			}
			if (need) {
				DepthFirstSearch(cur->nxt[i], height + 1, term_count, code_lengths, values);
			}
			need = false;
		}
	}
};

HuffmanTree::HuffmanTree() : impl_(new HuffmanTree::Impl()) {
}

void HuffmanTree::Build(const std::vector<uint8_t> &code_lengths,
						const std::vector<uint8_t> &values) {
	impl_->Build(code_lengths, values);
}

bool HuffmanTree::Move(bool bit, int &value) {
	return impl_->Move(bit, value);
}

HuffmanTree::HuffmanTree(HuffmanTree &&) = default;

HuffmanTree &HuffmanTree::operator=(HuffmanTree &&) = default;

HuffmanTree::~HuffmanTree() = default;
