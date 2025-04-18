import numpy as np
import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.svm import SVC
from sklearn.pipeline import make_pipeline
import joblib

def train_chatbot():
    data = {
        "query": [
            "Where is my order?",
            "I want to return a product",
            "How long does shipping take?",
            "Cancel my order",
            "How do I track my package?",
            "What is your refund policy?",
            "Hi",
            "Hello",
            "Goodbye",
            "Thanks",
            "Do you have discounts?",
            "What payment methods do you accept?",
            "How can I contact customer support?",
            "Do you ship internationally?",
            "What happens if my order is damaged?",
            "I received the wrong product.",
            "Can I change my shipping address after placing an order?",
            "What is the estimated delivery time for express shipping?",
            "How do I apply a promo code?",
            "Is cash on delivery available?"
        ],
        "response": [
            "Please provide your order ID to check the status.",
            "You can return products within 7 days of delivery.",
            "Standard shipping takes 3-5 business days.",
            "Please provide your order ID for cancellation.",
            "You can track your package using the tracking ID sent to your email.",
            "We offer refunds for returns within 7 days of delivery.",
            "Hello! How can I help you today?",
            "Hello! How can I assist you?",
            "Goodbye! Have a great day!",
            "You're welcome! Let me know if you need anything else.",
            "Yes! We offer seasonal discounts and special promo codes.",
            "We accept credit/debit cards, PayPal, and cash on delivery.",
            "You can contact support via email or our 24/7 chat service.",
            "Yes, we ship to selected international locations.",
            "Please contact support within 24 hours of delivery for damaged items.",
            "We apologize for the mistake! You can request an exchange or refund.",
            "Unfortunately, the shipping address cannot be changed once the order is placed.",
            "Express shipping takes 1-2 business days.",
            "You can enter your promo code at checkout to avail the discount.",
            "Yes, cash on delivery is available in selected locations."
        ]
    }

    df = pd.DataFrame(data)


    vectorizer = TfidfVectorizer()
    classifier = SVC(kernel="linear")
    pipeline = make_pipeline(vectorizer, classifier)

    pipeline.fit(df["query"], df["response"])


    joblib.dump(pipeline, "chatbot_model.pkl")
    print("Chatbot model trained and saved!")






def chatbot():
    print("Welcome to ShopEase! How can I assist you today?")


    model = joblib.load("chatbot_model.pkl")

    while True:
        user_input = input("You: ")
        if user_input.lower() in ["bye", "exit", "quit"]:
            print("Chatbot: Thank you for visiting ShopEase! Have a great day!")
            break

        response = model.predict([user_input])[0]
        print(f"Chatbot: {response}")

if __name__ == "__main__":
    train_chatbot()
    chatbot()