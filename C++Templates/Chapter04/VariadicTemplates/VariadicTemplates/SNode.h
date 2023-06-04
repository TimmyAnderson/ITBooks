#pragma once
//----------------------------------------------------------------------------------------------------------------------
struct SNode final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		// !!! FIELDS su PUBLIC, aby sa na ne dal ziskat POINTER na FIELD.
		SNode*													MLeftNode;
		SNode*													MRightNode;

	public:
		int GetValue(void) const noexcept;
		void SetLeftNode(SNode* Node);
		void SetRightNode(SNode* Node);

	public:
		SNode(int Value);
		virtual ~SNode(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------