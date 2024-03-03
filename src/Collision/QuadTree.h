#pragma once

/*
    Source: https://github.com/pvigier/Quadtree/blob/d205190a5e74527746acaade89309b33b00985c6/include/Quadtree.h
*/

#include <algorithm>
#include <array>
#include <cassert>
#include <memory>
#include <type_traits>
#include <vector>

#include "ExtRect.h"

namespace DayNNight {

    template <typename T, typename GetExtRect, typename Equal = std::equal_to<T>, typename Float = float>
    class Quadtree {
        /*static_assert(std::is_convertible_v<std::invoke_result_t<GetExtRect, const T&>, ExtRect<Float>>,
            "GetExtRect must be a callable of signature ExtRect<Float>(const T&)");
        static_assert(std::is_convertible_v<std::invoke_result_t<Equal, const T&, const T&>, bool>,
            "Equal must be a callable of signature bool(const T&, const T&)");
        static_assert(std::is_arithmetic_v<Float>);*/

       public:
        Quadtree(const ExtRect<Float>& box, const GetExtRect& getExtRect = GetExtRect(),
                 const Equal& equal = Equal()) : mExtRect(box), mRoot(std::make_unique<TreeNode>()), mGetExtRect(getExtRect), mEqual(equal) {
        }

        void add(const T& value) {
            add(mRoot.get(), 0, mExtRect, value);
        }

        void remove(const T& value) {
            remove(mRoot.get(), mExtRect, value);
        }

        std::vector<T> query(const ExtRect<Float>& box) const {
            auto values = std::vector<T>();
            query(mRoot.get(), mExtRect, box, values);
            return values;
        }

        std::vector<std::pair<T, T>> findAllIntersections() const {
            auto intersections = std::vector<std::pair<T, T>>();
            findAllIntersections(mRoot.get(), intersections);
            return intersections;
        }

        ExtRect<Float> getExtRect() const {
            return mExtRect;
        }
        struct TreeNode {
            std::array<std::unique_ptr<TreeNode>, 4> children;
            std::vector<T> values;
        };

        std::unique_ptr<TreeNode> mRoot;

       private:
        static constexpr auto Threshold = std::size_t(16);
        static constexpr auto MaxDepth = std::size_t(8);

        ExtRect<Float> mExtRect;
        // std::unique_ptr<TreeNode> mRoot;
        GetExtRect mGetExtRect;
        Equal mEqual;

        bool isLeaf(const TreeNode* node) const {
            return !static_cast<bool>(node->children[0]);
        }

        ExtRect<Float> computeExtRect(const ExtRect<Float>& box, int i) const {
            auto origin = box.getTopLeft();
            auto childSize = box.getSize() / static_cast<Float>(2);
            switch (i) {
                    // North West
                case 0:
                    return ExtRect<Float>(origin, childSize);
                    // Norst East
                case 1:
                    return ExtRect<Float>(sf::Vector2<Float>(origin.x + childSize.x, origin.y), childSize);
                    // South West
                case 2:
                    return ExtRect<Float>(sf::Vector2<Float>(origin.x, origin.y + childSize.y), childSize);
                    // South East
                case 3:
                    return ExtRect<Float>(origin + childSize, childSize);
                default:
                    assert(false && "Invalid child index");
                    return ExtRect<Float>();
            }
        }

        int getQuadrant(const ExtRect<Float>& nodeExtRect, const ExtRect<Float>& valueExtRect) const {
            auto center = nodeExtRect.getCenter();
            // West
            if (valueExtRect.getRight() < center.x) {
                // North West
                if (valueExtRect.getBottom() < center.y)
                    return 0;
                // South West
                else if (valueExtRect.top >= center.y)
                    return 2;
                // Not contained in any quadrant
                else
                    return -1;
            }
            // East
            else if (valueExtRect.left >= center.x) {
                // North East
                if (valueExtRect.getBottom() < center.y)
                    return 1;
                // South East
                else if (valueExtRect.top >= center.y)
                    return 3;
                // Not contained in any quadrant
                else
                    return -1;
            }
            // Not contained in any quadrant
            else
                return -1;
        }

        void add(TreeNode* node, std::size_t depth, const ExtRect<Float>& box, const T& value) {
            assert(node != nullptr);
            assert(box.contains(mGetExtRect(value)));
            if (isLeaf(node)) {
                // Insert the value in this node if possible
                if (depth >= MaxDepth || node->values.size() < Threshold)
                    node->values.push_back(value);
                // Otherwise, we split and we try again
                else {
                    split(node, box);
                    add(node, depth, box, value);
                }
            } else {
                auto i = getQuadrant(box, mGetExtRect(value));
                // Add the value in a child if the value is entirely contained in it
                if (i != -1)
                    add(node->children[static_cast<std::size_t>(i)].get(), depth + 1, computeExtRect(box, i), value);
                // Otherwise, we add the value in the current node
                else
                    node->values.push_back(value);
            }
        }

        void split(TreeNode* node, const ExtRect<Float>& box) {
            assert(node != nullptr);
            assert(isLeaf(node) && "Only leaves can be split");
            // Create children
            for (auto& child : node->children)
                child = std::make_unique<TreeNode>();
            // Assign values to children
            auto newValues = std::vector<T>();  // New values for this node
            for (const auto& value : node->values) {
                auto i = getQuadrant(box, mGetExtRect(value));
                if (i != -1)
                    node->children[static_cast<std::size_t>(i)]->values.push_back(value);
                else
                    newValues.push_back(value);
            }
            node->values = std::move(newValues);
        }

        bool remove(TreeNode* node, const ExtRect<Float>& box, const T& value) {
            assert(node != nullptr);
            assert(box.contains(mGetExtRect(value)));
            if (isLeaf(node)) {
                // Remove the value from node
                removeValue(node, value);
                return true;
            } else {
                // Remove the value in a child if the value is entirely contained in it
                auto i = getQuadrant(box, mGetExtRect(value));
                if (i != -1) {
                    if (remove(node->children[static_cast<std::size_t>(i)].get(), computeExtRect(box, i), value))
                        return tryMerge(node);
                }
                // Otherwise, we remove the value from the current node
                else
                    removeValue(node, value);
                return false;
            }
        }

        void removeValue(TreeNode* node, const T& value) {
            // Find the value in node->values
            auto it = std::find_if(std::begin(node->values), std::end(node->values),
                                   [this, &value](const auto& rhs) { return mEqual(value, rhs); });
            assert(it != std::end(node->values) && "Trying to remove a value that is not present in the node");
            // Swap with the last element and pop back
            *it = std::move(node->values.back());
            node->values.pop_back();
        }

        bool tryMerge(TreeNode* node) {
            assert(node != nullptr);
            assert(!isLeaf(node) && "Only interior nodes can be merged");
            auto nbValues = node->values.size();
            for (const auto& child : node->children) {
                if (!isLeaf(child.get()))
                    return false;
                nbValues += child->values.size();
            }
            if (nbValues <= Threshold) {
                node->values.reserve(nbValues);
                // Merge the values of all the children
                for (const auto& child : node->children) {
                    for (const auto& value : child->values)
                        node->values.push_back(value);
                }
                // Remove the children
                for (auto& child : node->children)
                    child.reset();
                return true;
            } else
                return false;
        }

        void query(TreeNode* node, const ExtRect<Float>& box, const ExtRect<Float>& queryExtRect, std::vector<T>& values) const {
            assert(node != nullptr);
            assert(queryExtRect.intersects(box));
            for (const auto& value : node->values) {
                if (queryExtRect.intersects(mGetExtRect(value)))
                    values.push_back(value);
            }
            if (!isLeaf(node)) {
                for (auto i = std::size_t(0); i < node->children.size(); ++i) {
                    auto childExtRect = computeExtRect(box, static_cast<int>(i));
                    if (queryExtRect.intersects(childExtRect))
                        query(node->children[i].get(), childExtRect, queryExtRect, values);
                }
            }
        }

        void findAllIntersections(TreeNode* node, std::vector<std::pair<T, T>>& intersections) const {
            // Find intersections between values stored in this node
            // Make sure to not report the same intersection twice
            for (auto i = std::size_t(0); i < node->values.size(); ++i) {
                for (auto j = std::size_t(0); j < i; ++j) {
                    if (mGetExtRect(node->values[i]).intersects(mGetExtRect(node->values[j])))
                        intersections.emplace_back(node->values[i], node->values[j]);
                }
            }
            if (!isLeaf(node)) {
                // Values in this node can intersect values in descendants
                for (const auto& child : node->children) {
                    for (const auto& value : node->values)
                        findIntersectionsInDescendants(child.get(), value, intersections);
                }
                // Find intersections in children
                for (const auto& child : node->children)
                    findAllIntersections(child.get(), intersections);
            }
        }

        void findIntersectionsInDescendants(TreeNode* node, const T& value, std::vector<std::pair<T, T>>& intersections) const {
            // Test against the values stored in this node
            for (const auto& other : node->values) {
                if (mGetExtRect(value).intersects(mGetExtRect(other)))
                    intersections.emplace_back(value, other);
            }
            // Test against values stored into descendants of this node
            if (!isLeaf(node)) {
                for (const auto& child : node->children)
                    findIntersectionsInDescendants(child.get(), value, intersections);
            }
        }
    };

}  // namespace DayNNight